/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 22:24:40 by apedron           #+#    #+#             */
/*   Updated: 2018/04/06 16:16:11 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	exit [n]
**	Cause the shell to exit.
**	-------------------------------------------------------------------------- +
*/

int	my_exit(char **args, int *status)
{
	extern char	**environ;
	int			i;

	i = 1;
	def_term_mode(TERM_RESET);
	ft_putendl_fd("exit", STDERR_FILENO);
	if (!args[1])
	{
		ft_arrfree(environ);
		ft_arrfree(args);
		free_hist(&g_hist);
		exit(g_status);
	}
	if (args[2])
		ft_putendl("exit: too many arguments");
	else
	{
		i = ft_atoi(args[1]);
		ft_arrfree(environ);
		ft_arrfree(args);
		free_hist(&g_hist);
		exit(i);
	}
	return ((*status = 1));
}
