/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_atoi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:59:11 by gcadiou           #+#    #+#             */
/*   Updated: 2017/11/01 04:38:55 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		calcul_nb_int(char *s)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (ISSPACE(s, i))
		i++;
	while (s[i])
	{
		while (NOSPACE(s, i) && s[i])
			i++;
		while (ISSPACE(s, i))
			i++;
		x++;
	}
	return (x);
}

int		ft_strsplit_atoi(int **int_tab, char *s)
{
	char	**char_tab;
	int		i;
	int		x;

	if (!s)
		return (0);
	i = 0;
	x = calcul_nb_int(s);
	char_tab = ft_strsplit_whitespace(s);
	*int_tab = ft_memalloc(sizeof(int) * x);
	while (char_tab[i])
	{
		(*int_tab)[i] = ft_atoi(char_tab[i]);
		i++;
	}
	return (x);
}
