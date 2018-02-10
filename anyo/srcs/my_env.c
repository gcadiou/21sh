/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:43:59 by apedron           #+#    #+#             */
/*   Updated: 2018/01/13 18:27:04 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Check if an argument is a valid entry.
**	-------------------------------------------------------------------------- +
*/

static int	entry_is_valid(char *entry)
{
	int	i;

	i = 0;
	if (ft_isprint(*(entry + 0)) == TRUE &&
			*(entry + 0) != '=' && *(entry + 0) != '-')
	{
		while (*(entry + i))
			if (*(entry + i++) == '=')
				return (TRUE);
	}
	return (FALSE);
}

/*
**	-------------------------------------------------------------------------- +
**	Add entries from the command line to the new environ.
**	-------------------------------------------------------------------------- +
*/

static int	append_entries(t_env **new_env, char *entry)
{
	char	*entry_name;
	char	*entry_value;
	int		i;

	i = 0;
	while (*(entry + i) && *(entry + i) != '=')
		i++;
	if (!(entry_name = ft_strndup(entry, i)))
		return (EXIT_FAILURE);
	if (!(entry_value = ft_strrdup(entry, (i + 1))))
		return (EXIT_FAILURE);
	env_append(new_env, entry_name, entry_value);
	ft_strdel(&entry_name);
	ft_strdel(&entry_value);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Create the new environ to display, or to pass to a utility.
**	-------------------------------------------------------------------------- +
*/

static int	get_new_env(t_env **new_env, t_env **env, char **command)
{
	t_env	*node;
	int		i;

	if ((*(command + 1) && ft_strncmp(*(command + 1), "-i\0", 3) != 0 &&
			ft_strncmp(*(command + 1), "-\0", 2) != 0) || !*(command + 1))
	{
		node = *env;
		while (node)
		{
			env_append(new_env, node->name, node->value);
			node = node->next;
		}
		i = 1;
	}
	else
		i = 2;
	while (*(command + i) && entry_is_valid(*(command + i)) == TRUE)
	{
		if (append_entries(new_env, *(command + i)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Create the new command to execute with the new environ.
**	-------------------------------------------------------------------------- +
*/

static char	**get_new_cmd(char **command)
{
	char	**ret;
	int		len;
	int		i;
	int		j;

	i = 1;
	j = 0;
	len = 0;
	if (*(command + 1))
	{
		if (ft_strncmp(*(command + 1), "-i\0", 3) == 0 ||
				ft_strncmp(*(command + 1), "-\0", 2) == 0)
			i++;
		while (*(command + i) && entry_is_valid(*(command + i)) == TRUE)
			i++;
		len = ft_arrlen(command) - i;
	}
	if (!(ret = ft_memalloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (*(command + i))
		if (!(*(ret + j++) = ft_strdup(*(command + i++))))
			return (NULL);
	*(ret + j) = NULL;
	return (ret);
}

/*
**	-------------------------------------------------------------------------- +
**	Implementation of the builtin `env [-i]`
**	The env utility accepts the - option as a synonym for -i.
**	-------------------------------------------------------------------------- +
*/

int			my_env(t_env **env, char **command)
{
	t_env	*new_env;
	char	**new_cmd;

	new_env = NULL;
	if (ft_strncmp(*(command + 0), "env\0", 4) != 0)
		return (0);
	else
	{
		if (get_new_env(&new_env, env, command) == EXIT_FAILURE)
			return (-1);
		env_reverse(&new_env);
		if (!(new_cmd = get_new_cmd(command)))
			return (-1);
		if (is_command_empty(new_cmd) == TRUE)
			env_print(new_env);
		else
		{
			if (cmd_execute(&new_env, new_cmd) == EXIT_FAILURE)
				return (-1);
		}
		env_free(&new_env);
		ft_arrfree(new_cmd);
	}
	return (1);
}
