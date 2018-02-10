/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 16:00:40 by apedron           #+#    #+#             */
/*   Updated: 2018/01/17 21:55:12 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Saves terminal settings (mode > 0), or resets them back as it was before
**	the call to raw_term_mode() function (mode < 0).
**	-------------------------------------------------------------------------- +
*/

int	def_term_mode(int mode)
{
	static struct termios	*attr_save = NULL;

	if (mode > 0)
	{
		if (!(attr_save = ft_memalloc(sizeof(struct termios))))
			return (EXIT_FAILURE);
		if (tcgetattr(STDIN_FILENO, attr_save) == -1)
		{
			ft_putendl_fd("error: could not get termios.", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	if (mode < 0)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, attr_save) == -1)
		{
			ft_putendl_fd("error: could not set terminal.", STDERR_FILENO);
			return (EXIT_SUCCESS);
		}
		ft_free(attr_save);
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Saves all terminal settings & turns on raw mode for the current terminal.
**	To do so, it disables canonical input mode, echo mode & signals, and
**	changes special parameters MIN & TIME (which controls input settings)
**	-------------------------------------------------------------------------- +
*/

int	raw_term_mode(void)
{
	struct termios	attr;

	def_term_mode(1);
	if (tcgetattr(STDIN_FILENO, &attr) == -1)
	{
		ft_putendl_fd("error: could not get termios.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	attr.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	attr.c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON);
	attr.c_oflag |= (CS8);
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &attr) == -1)
	{
		ft_putendl_fd("error: could not set terminal.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
