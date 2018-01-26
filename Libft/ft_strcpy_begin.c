/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_begin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:55:27 by gcadiou           #+#    #+#             */
/*   Updated: 2017/09/23 18:16:09 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy_begin(char *s, int size)
{
	int		i;
	char	*new;

	i = ft_strlen(s) - size;
	new = ft_strnew(i);
	new = ft_strncpy(new, s, i);
	new[i] = '\0';
	return (new);
}
