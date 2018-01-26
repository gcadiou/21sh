/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsecmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 03:35:53 by gcadiou           #+#    #+#             */
/*   Updated: 2017/10/23 08:15:14 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		next_quote(char *cmd, int i)
{
	while (cmd[i])
	{
		if (DOUBLEQUOTE(cmd, i))
			return (i + 1);
		i++;
	}
	return (-1);
}

int		end_nospace(char *cmd, int i)
{
	while (NOSPACE(cmd, i) && cmd[i])
		i++;
	return (i);
}

int		calcul_nb_args(char *cmd)
{
	int		i;
	int		args;

	i = 0;
	args = 0;
	while (cmd[i])
	{
		while (ISSPACE(cmd, i))
			i++;
		if (DOUBLEQUOTE(cmd, i))
		{
			if ((i = next_quote(cmd, i + 1)) == -1)
				return (-1);
			else
				args++;
			continue;
		}
		if (!(DOUBLEQUOTE(cmd, i)) && cmd[i])
			args++;
		while (NOSPACE(cmd, i) && cmd[i] && !(DOUBLEQUOTE(cmd, i)))
			i++;
	}
	return (args);
}

int		fill_tab(char **tab, char *cmd, int args, int i)
{
	while (ISSPACE(cmd, i))
		i++;
	if (DOUBLEQUOTE(cmd, i))
	{
		tab[args] = ft_strsub(cmd, i + 1, (next_quote(cmd, i + 1) - i) - 2);
		i = next_quote(cmd, i + 1);
		return (i);
	}
	tab[args] = ft_strsub(cmd, i, end_nospace(cmd, i) - i);
	i = end_nospace(cmd, i);
	return (i);
}

char	**ft_parsecmd(char *cmd)
{
	char	**tab;
	int		nb_args;
	int		i;
	int		args;

	i = 0;
	args = 0;
	if ((nb_args = calcul_nb_args(cmd)) == -1)
	{
		ft_putendl_fd("quote not closed", 2);
		return (NULL);
	}
	tab = ft_memalloc(sizeof(char *) * (nb_args + 1));
	while (args < nb_args)
	{
		i = fill_tab(tab, cmd, args, i);
		args++;
	}
	tab[args] = NULL;
	return (tab);
}
