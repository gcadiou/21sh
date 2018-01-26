/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_endcpy_until.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:50:35 by gcadiou           #+#    #+#             */
/*   Updated: 2017/09/25 23:20:32 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_endcpy_until(char *s, char c)
{
	int		i;
	char	*tmp;
	char	*new;

	tmp = ft_strrchr(s, c);
	if (tmp == 0)
		return (ft_strdup(s));
	i = ft_strlen(tmp);
	new = ft_memalloc(sizeof(char) * (i + 1));
	check_malloc(new, "ft_strcut_until");
	return (ft_strcpy(new, tmp));
}
