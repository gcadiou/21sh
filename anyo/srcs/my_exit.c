/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:10:21 by apedron           #+#    #+#             */
/*   Updated: 2018/01/15 20:01:04 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Implementation of the builtin `exit [status]`.
**	An optional exit code (status) can be specified, which is a simple
**	integer value that is then returned to the parent shell.
**
**	Custom aliases for exit are "lo", "bye" and "logout".
**	-------------------------------------------------------------------------- +
*/

int	my_exit(t_env **env, char **command)
{
	int status;

	status = 0;
	if (ft_strncmp(*(command + 0), "exit\0", 5) != 0 &&
		ft_strncmp(*(command + 0), "lo\0", 3) != 0 &&
		ft_strncmp(*(command + 0), "bye\0", 4) != 0 &&
		ft_strncmp(*(command + 0), "logout\0", 7) != 0)
		return (0);
	if (*(command + 1))
		status = ft_atoi(*(command + 1));
	ft_arrfree(command);
	env_free(env);
	ft_putendl("exit");
	exit(status);
}
