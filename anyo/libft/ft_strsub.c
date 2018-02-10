/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:27:59 by anyo              #+#    #+#             */
/*   Updated: 2017/11/30 16:41:41 by anyo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Allocates (with malloc(3)) and returns a “fresh” substring from the string
**	given as argument.
**	The substring begins at index `start` and is of size `len`.
**	If `start` and `len` aren’t refering to a valid substring, the behavior is
**	undefined.
**	If the allocation fails, the function returns NULL.
**	-------------------------------------------------------------------------- +
*/

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s || !(ptr = ft_strnew(len)))
		return (NULL);
	while (len > i)
		*(ptr + i++) = *(s + start++);
	*(ptr + i) = '\0';
	return (ptr);
}
