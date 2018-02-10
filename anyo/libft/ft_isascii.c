/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 19:04:55 by anyo              #+#    #+#             */
/*   Updated: 2017/11/30 16:28:41 by anyo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 isascii
**	-------------------------------------------------------------------------- +
*/

int		ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}