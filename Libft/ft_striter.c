/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:42:40 by anyo              #+#    #+#             */
/*   Updated: 2017/11/30 16:36:30 by anyo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Applies the function `f` to each character of the string passed as argument.
**	Each character is passed by address to `f` to be modified if necessary.
**	-------------------------------------------------------------------------- +
*/

void	ft_striter(char *s, void (*f)(char *))
{
	size_t	i;

	i = -1;
	if (s && f)
		while (*(s + ++i))
			f(s + i);
}
