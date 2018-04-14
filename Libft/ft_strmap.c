/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:50:54 by anyo              #+#    #+#             */
/*   Updated: 2017/11/30 16:38:11 by anyo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Applies the function `f` to each character of the string given as argument
**	to create a “fresh” new string (with malloc(3)) resulting from the
**	successive applications of `f`.
**	-------------------------------------------------------------------------- +
*/

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*ptr;

	i = -1;
	if (!s || !(ptr = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (*(s + ++i))
		*(ptr + i) = f(*(s + i));
	*(ptr + i) = '\0';
	return (ptr);
}
