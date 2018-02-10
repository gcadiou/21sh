/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_until.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:56:10 by gcadiou           #+#    #+#             */
/*   Updated: 2018/02/10 18:37:47 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy_until(char *s, char c)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = (char*)ft_memalloc(sizeof(char) * (ft_strlentil(s, c) + 1))))
		return (0);
	while (s[i] != c)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
