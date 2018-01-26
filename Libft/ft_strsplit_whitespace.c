/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_whitespace.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 05:33:43 by gcadiou           #+#    #+#             */
/*   Updated: 2017/09/25 15:25:08 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strlentil(const char *s, size_t i)
{
	size_t	count;

	count = 0;
	while (s[i] && !(ISSPACE(s, i)))
	{
		count++;
		i++;
	}
	return (count);
}

static int	calcnbwords(char const *s)
{
	int		nbwords;
	size_t	i;

	i = 0;
	nbwords = 0;
	if (ISSPACE(s, i))
		nbwords--;
	while (s[i])
	{
		while (!(ISSPACE(s, i)) && s[i])
			i++;
		nbwords++;
		while (ISSPACE(s, i))
			i++;
	}
	return (nbwords);
}

static int	vivelanorme(char const *s, int numwords)
{
	int		is;
	int		it;

	is = 0;
	it = 0;
	while (it++ != numwords)
	{
		while (ISSPACE(s, is))
			is++;
		while (s[is] && !(ISSPACE(s, is)))
			is++;
	}
	while (ISSPACE(s, is))
		is++;
	return (is);
}

static char	**filltab(char **tab, char const *s, int numwords)
{
	int		it1;
	size_t	is;
	size_t	it2;

	it2 = 0;
	it1 = 0;
	is = vivelanorme(s, numwords);
	if (!(tab[numwords] =
				(char *)malloc(sizeof(char) * strlentil(s, is) + 1)))
		return (0);
	while (!(ISSPACE(s, is)) && s[is])
	{
		tab[numwords][it2] = s[is];
		is++;
		it2++;
	}
	tab[numwords][it2] = '\0';
	return (0);
}

char		**ft_strsplit_whitespace(char const *s)
{
	char	**tab;
	int		nbwords;
	int		numwords;

	if (!s)
		return (NULL);
	nbwords = calcnbwords(s);
	if (!(tab = (char **)malloc(sizeof(*tab) * (nbwords + 1))))
		return (NULL);
	numwords = 0;
	while (numwords < nbwords)
	{
		filltab(tab, s, numwords);
		numwords++;
	}
	tab[numwords] = 0;
	return (tab);
}
