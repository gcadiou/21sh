/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:11:41 by gcadiou           #+#    #+#             */
/*   Updated: 2018/04/02 21:34:31 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	unsetenv name [... ]
**	Deletes the variable(s) `name` from the environment.
**	If `name` does not exist in the environment, then the function succeeds,
**	and the environment is unchanged.
**
**	Return -1, EXIT_SUCCESS or EXIT_FAILURE only.
**	-------------------------------------------------------------------------- +
*/

int	my_unsetenv(char **args, int *status)
{
	int x;

	if (ft_arrlen(args) == 1)
	{
		ft_putendl_fd("unsetenv: too few arguments", STDERR_FILENO);
		return ((*status = 1));
	}
	x = 1;
	while (args[x])
	{
		if (env_remove(args[x]) == EXIT_FAILURE)
			return ((*status = -1));
		x++;
	}
	return ((*status = 0));
}
