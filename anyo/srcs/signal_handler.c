/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 20:02:17 by apedron           #+#    #+#             */
/*   Updated: 2018/02/08 15:11:43 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Executed when an INT ("interrupt") signal has been received in the program
**	(main loop). This causes the process to terminate.
**	It also sends a custom byte in the input queue, which call a function that..
**	-------------------------------------------------------------------------- +
*/

void	sig_int(int sig)
{
	char	byte[2];

	if (sig == SIGINT)
	{
		byte[0] = KP_CTRL_C;
		byte[1] = '\0';
		ioctl(STDIN_FILENO, TIOCSTI, byte);
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Executed when an INT ("interrupt") signal has been received in the program
**	on a RUNNING PROCESS. It does not print a newline character, and does not
**	call a custom function.
**	-------------------------------------------------------------------------- +
*/

void	sig_exe(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		signal(SIGINT, sig_exe);
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Does nothing on TSTP ("terminal stop") signals.
**	-------------------------------------------------------------------------- +
*/

void	sig_tstp(int sig)
{
	(void)sig;
}

/*
**	-------------------------------------------------------------------------- +
**	Initializes all signal handling functions needed.
**	-------------------------------------------------------------------------- +
*/

void	signal_handler(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, sig_int);
		signal(SIGTSTP, sig_tstp);
	}
	else if (mode == 1)
		signal(SIGINT, sig_exe);
}
