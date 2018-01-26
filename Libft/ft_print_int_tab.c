/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:31:50 by gcadiou           #+#    #+#             */
/*   Updated: 2017/10/31 18:34:05 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_int_tab(int **tab, int l, int i, char c)
{
	int		i1;
	int		i2;

	i1 = 0;
	while (i1 < l)
	{
		i2 = 0;
		while (i2 < i)
		{
			ft_putnbr(tab[i1][i2]);
			i2++;
		}
		ft_putchar(c);
		i1++;
	}
}
