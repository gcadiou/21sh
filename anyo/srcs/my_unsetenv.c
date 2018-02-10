/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:35:21 by apedron           #+#    #+#             */
/*   Updated: 2018/01/13 18:28:47 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Displays the errors/usage on the standard error output.
**	-------------------------------------------------------------------------- +
*/

static void	my_usage(char **command, int status)
{
	if (status == 1)
	{
		ft_putendl_fd("unsetenv: incorrect formatting", STDERR_FILENO);
		ft_putendl_fd("usage: unsetenv [name]", STDERR_FILENO);
	}
	if (status == 2)
	{
		ft_putstr_fd("unsetenv: incorrect element name: ", STDERR_FILENO);
		ft_putendl_fd(*(command + 1), STDERR_FILENO);
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Incomplete implementation of the builtin `unset`.
**	-------------------------------------------------------------------------- +
*/

int			my_unsetenv(t_env **env, char **command)
{
	if (ft_strncmp(*(command + 0), "unsetenv\0", 9) != 0)
		return (0);
	else if (ft_arrlen(command) != 2)
		my_usage(command, 1);
	else if (env_entry_exists(env, *(command + 1)) == FALSE)
		my_usage(command, 2);
	else
		env_remove(env, *(command + 1));
	return (1);
}
