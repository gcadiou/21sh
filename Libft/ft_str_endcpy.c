/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_endcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:53:12 by gcadiou           #+#    #+#             */
/*   Updated: 2017/09/25 15:24:19 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_endcpy(char *s, int i)
{
	char	*new;
	int		l;

	l = 0;
	new = ft_strnew(ft_strlen(s) - i + 1);
	while (s[i])
	{
		new[l] = s[i];
		i++;
		l++;
	}
	new[l] = '\0';
	return (new);
}
