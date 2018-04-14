/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:37:55 by anyo              #+#    #+#             */
/*   Updated: 2018/01/29 17:55:05 by anyo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Returns the result of the concatenation of `s1` and at most `n`
**	characters from `s2`, ending with '\0'.
**	-------------------------------------------------------------------------- +
*/

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*ptr;

	if (!s1 || s2 || !(ptr = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(ptr, s1);
	ft_strncat(ptr, s2, n);
	return (ptr);
}
