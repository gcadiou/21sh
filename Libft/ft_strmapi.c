/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:21:17 by anyo              #+#    #+#             */
/*   Updated: 2017/11/30 16:38:51 by anyo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Applies the function `f` to each character of the string passed as argument
**	by giving its index as first argument to create a “fresh” new string
**	(with malloc(3)) resulting from the successive applications of `f`.
**	-------------------------------------------------------------------------- +
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ptr;

	i = -1;
	if (!s || !(ptr = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (*(s + ++i))
		*(ptr + i) = f(i, *(s + i));
	*(ptr + i) = '\0';
	return (ptr);
}
