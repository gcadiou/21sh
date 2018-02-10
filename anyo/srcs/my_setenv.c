/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:29:28 by apedron           #+#    #+#             */
/*   Updated: 2018/01/13 18:29:05 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Checks if an argument is a valid entry name.
**	-------------------------------------------------------------------------- +
*/

static int	entry_is_valid(char *entry)
{
	unsigned long	i;

	i = 0;
	if (ft_isprint(*(entry + 0)) == TRUE &&
			*(entry + 0) != '=' && *(entry + 0) != '-')
	{
		while (*(entry + i) && ft_isprint(*(entry + i)))
			i++;
		if (ft_strlen(entry) == i)
			return (TRUE);
	}
	return (FALSE);
}

/*
**	-------------------------------------------------------------------------- +
**	Displays the errors/usage on the standard error output.
**	-------------------------------------------------------------------------- +
*/

static void	my_usage(char **command, int status)
{
	if (status == 1)
	{
		ft_putendl_fd("setenv: incorrect formatting", STDERR_FILENO);
		ft_putendl_fd("usage: setenv [name=value]", STDERR_FILENO);
	}
	if (status == 2)
	{
		ft_putstr_fd("setenv: not valid in this context: ", STDERR_FILENO);
		ft_putendl_fd(*(command + 1), STDERR_FILENO);
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Incomplete implementation of the builtin `export`.
**	-------------------------------------------------------------------------- +
*/

int			my_setenv(t_env **env, char **command)
{
	char	*entry_name;
	char	*entry_value;
	int		i;

	i = 0;
	if (ft_strncmp(*(command + 0), "setenv\0", 7) != 0)
		return (0);
	else if (ft_arrlen(command) != 2 || !ft_strchr(*(command + 1), '='))
		my_usage(command, 1);
	else
	{
		while (command[1][i] && command[1][i] != '=')
			i++;
		if (!(entry_name = ft_strndup(*(command + 1), i)))
			return (-1);
		if (!(entry_value = ft_strrdup(*(command + 1), i + 1)))
			return (-1);
		if (entry_is_valid(entry_name) == TRUE)
			env_append(env, entry_name, entry_value);
		else
			my_usage(command, 2);
		ft_strdel(&entry_name);
		ft_strdel(&entry_value);
	}
	return (1);
}
