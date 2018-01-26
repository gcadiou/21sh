/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut_until.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 08:38:24 by gcadiou           #+#    #+#             */
/*   Updated: 2017/09/23 21:13:05 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut_until(char *s, char c)
{
	char	*new;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (s[i] != c)
		i++;
	new = malloc(sizeof(char) * (ft_strlen(&(s[i])) + 1));
	while (s[i])
	{
		new[x] = s[i];
		i++;
		x++;
	}
	new[x] = '\0';
	free(s);
	return (new);
}
