/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:35:32 by anyo              #+#    #+#             */
/*   Updated: 2017/11/30 16:51:20 by anyo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Lexicographical comparison between `s1` and `s2` up to `n` characters or
**	until a ’\0’ is reached.
**	If the two strings are identical, the function returns 1, or 0 otherwise.
**	-------------------------------------------------------------------------- +
*/

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 || !s2)
		return (0);
	return (!ft_strncmp(s1, s2, n));
}
