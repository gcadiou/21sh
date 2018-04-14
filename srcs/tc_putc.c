/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 18:31:32 by apedron           #+#    #+#             */
/*   Updated: 2018/03/14 17:45:57 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	tc_putc() is a putchar-like routine to which the characters are passed,
**	one at a time, and is here to work with tputs(3).
**	It prints the passed byte, then returns the return value of write() call.
**	-------------------------------------------------------------------------- +
*/

int	tc_putc(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}
