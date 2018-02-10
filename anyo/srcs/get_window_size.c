/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 17:28:44 by apedron           #+#    #+#             */
/*   Updated: 2018/01/14 20:02:24 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Stores screen rows and cols in ints, and returns status.
**	-------------------------------------------------------------------------- +
*/

int	get_window_size(int *rows, int *cols)
{
	struct winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return (EXIT_FAILURE);
	else
	{
		*cols = ws.ws_col;
		*rows = ws.ws_row;
	}
	return (EXIT_SUCCESS);
}
