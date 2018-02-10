/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:24:36 by apedron           #+#    #+#             */
/*   Updated: 2018/01/13 18:26:15 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Tries to print the matching value of the echo-ed $NAME.
**	-------------------------------------------------------------------------- +
*/

static int	put_env_val(t_env **env, char *name)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (ft_strcmp(node->name, name + 1) == 0)
		{
			ft_putstr(node->value);
			return (1);
		}
		node = node->next;
	}
	return (0);
}

/*
**	-------------------------------------------------------------------------- +
**	Implementation of the builtin `echo [-n]`.
**	When used without any options or strings, echo returns a blank line.
**	When a string is provided as argument, echo simply repeats this string.
**	The -n option can be used to stop echo from adding the newline to output.
**	If a word is preceded directly (i.e., with no intervening spaces) by the
**	dollar character ($), it is substituted by the value of the variable for
**	its name in the current environment.
**	-------------------------------------------------------------------------- +
*/

int			my_echo(t_env **env, char **command)
{
	int	has_been_printed;
	int	i;

	if (ft_strncmp(*(command + 0), "echo\0", 5) != 0)
		return (0);
	if (ft_arrlen(command) == 1)
		ft_putchar('\n');
	else
	{
		i = ft_strncmp(*(command + 1), "-n\0", 3) == 0 ? 2 : 1;
		while (*(command + i))
		{
			has_been_printed = 1;
			if (ft_strncmp(*(command + i), "$", 1) == 0)
				has_been_printed = put_env_val(env, *(command + i));
			else
				ft_putstr(*(command + i));
			if (*(command + i + 1))
				ft_putchar(has_been_printed == 1 ? ' ' : 0);
			else if (ft_strncmp(*(command + 1), "-n\0", 3) != 0)
				ft_putchar('\n');
			i++;
		}
	}
	return (1);
}
