/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 22:27:59 by apedron           #+#    #+#             */
/*   Updated: 2018/04/02 19:57:25 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	echo [string ...]
**	Write arguments to the standard output.
**
**	Return EXIT_SUCCESS only.
**	-------------------------------------------------------------------------- +
*/

int	my_echo(char **args, int *status)
{
	int	i;

	i = 1;
	if (args[1])
	{
		while (args[i])
		{
			ft_putstr(args[i]);
			if (args[i++ + 1])
				ft_putchar(' ');
		}
	}
	ft_putchar('\n');
	*status = 0;
	return (EXIT_SUCCESS);
}
