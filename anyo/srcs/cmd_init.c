/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 15:17:12 by apedron           #+#    #+#             */
/*   Updated: 2018/01/29 18:08:29 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Removes quotes in the given string, before adding it to the commands array.
**	-------------------------------------------------------------------------- +
*/

static char	*cmd_del_quotes(t_env **head, char *raw_str)
{
	char	*new_str;
	char	*tmp;

	if (raw_str && (*raw_str == '\'' || *raw_str == '\"'))
	{
		if (!(new_str = ft_strsub(raw_str, 1, (ft_strlen(raw_str) - 2))))
			return (NULL);
		ft_strdel(&raw_str);
		return (new_str);
	}
	else if (ft_strncmp(raw_str, "~", 1) == 0)
	{
		if (!(env_get_val(head, "HOME")))
		{
			ft_putendl_fd("21sh: can not interpret tild (`~').", STDERR_FILENO);
			return (raw_str);
		}
		if (!(tmp = ft_strdup(raw_str + 1)))
			return (NULL);
		ft_strdel(&raw_str);
		if (!(raw_str = ft_strjoin(env_get_val(head, "HOME"), tmp)))
			return (NULL);
		ft_strdel(&tmp);
	}
	return (raw_str);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns a copy of the word at the given index in the string.
**	-------------------------------------------------------------------------- +
*/

static char	*cmd_dup_index(const char *raw_input, int index)
{
	char	*ret;
	int		firstc;
	int		lastc;
	int		i;

	i = 0;
	if ((firstc = words_first_c(raw_input, index)) == -1)
		return (NULL);
	if ((lastc = words_last_c(raw_input, index)) == -1)
		return (NULL);
	if (!(ret = ft_strnew((lastc - firstc + 1))))
		return (NULL);
	while (firstc < (lastc + 1))
	{
		*(ret + i) = *(raw_input + firstc);
		firstc++;
		i++;
	}
	*(ret + i) = '\0';
	return (ret);
}

/*
**	-------------------------------------------------------------------------- +
**	Splits the input string into an array of strings, removing all blank
**	characters (those outside the quotes).
**	-------------------------------------------------------------------------- +
*/

static char	**cmd_format(t_env **head, const char *raw_input)
{
	char	**new_input;
	int		size;
	int		i;

	i = 0;
	size = words_count(raw_input);
	if (!(new_input = ft_memalloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		if (!(*(new_input + i) = cmd_del_quotes(head,
				cmd_dup_index(raw_input, i))))
			return (NULL);
		i++;
	}
	*(new_input + i) = NULL;
	return (new_input);
}

/*
**	-------------------------------------------------------------------------- +
**	Creates the linked list which is composed of multiple arrays for the
**	command input, if there is a semicolon (`;') or more in the string.
**	-------------------------------------------------------------------------- +
*/

int			cmd_init(t_cmd **head, t_env **env, char *input)
{
	char	**arr;
	t_cmd	*node;
	int		i;

	i = 0;
	if (!(arr = cmd_split(input)))
		return (EXIT_FAILURE);
	while (i < (int)ft_arrlen(arr))
	{
		if (!(node = ft_memalloc(sizeof(t_cmd))))
			return (EXIT_FAILURE);
		if (!(node->command = cmd_format(env, *(arr + i))))
			return (EXIT_FAILURE);
		node->next = *head;
		*head = node;
		i++;
	}
	ft_arrfree(arr);
	cmd_reverse(head);
	return (EXIT_SUCCESS);
}
