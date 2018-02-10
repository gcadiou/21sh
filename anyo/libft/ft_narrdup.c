/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_narrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 22:26:51 by gcadiou           #+#    #+#             */
/*   Updated: 2018/02/10 23:42:27 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_narrdup(char **arr, int size)
{
	char	**ret;
	int		i;
	int		n;

	n = ft_arrlen(arr);
	i = 0;
	if (!arr || !(ret = ft_memalloc(sizeof(char *) *
						(n + size + 1))))
		return (NULL);
	while (i < n && i < (n + size))
	{
		if (!(*(ret + i) = ft_strdup(*(arr + i))))
			return (NULL);
		i++;
	}
	*(ret + i) = NULL;
	return (ret);
}
