/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:50:27 by anyo              #+#    #+#             */
/*   Updated: 2017/11/30 16:31:54 by anyo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Allocates (with malloc(3)) and returns a “fresh” memory area.
**	The memory allocated is initialized to 0.
**	If the allocation fails, the function returns NULL.
**	-------------------------------------------------------------------------- +
*/

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = malloc(size)))
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}
