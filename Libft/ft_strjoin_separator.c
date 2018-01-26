/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_separator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:59:38 by gcadiou           #+#    #+#             */
/*   Updated: 2017/10/02 17:53:41 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_separator(char *prefix, char *suffix, char *separator,
									int f)
{
	char	*tmp;
	char	*final;

	tmp = ft_strjoin(prefix, separator);
	final = ft_strjoin(tmp, suffix);
	if (f == 1)
		ft_free(prefix);
	else if (f == 2)
		ft_free(suffix);
	else if (f == 3)
	{
		ft_free(prefix);
		ft_free(suffix);
	}
	ft_free(tmp);
	return (final);
}
