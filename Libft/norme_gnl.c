/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 00:13:25 by gcadiou           #+#    #+#             */
/*   Updated: 2017/09/16 04:29:50 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			norme_old_to_new(t_gnl *gnl, int i, int i2)
{
	gnl->str_new[i2] = gnl->str_old[i];
	free(gnl->str_old);
	return (0);
}

int			norme_gnl(t_gnl *gnl, char **line, int act)
{
	if (gnl[act].notfirst == 1)
		if (old_to_new(&(gnl[act])))
		{
			*line = gnl[act].str_new;
			return (1);
		}
	return (0);
}

int			norme_gnl_free(t_gnl **gnl, char **line, int act)
{
	int		i;
	int		x;

	x = 0;
	i = 0;
	if (gnl[act]->str_new != NULL)
		free(gnl[act]->str_new);
	while (gnl[i]->last != 1)
	{
		x += gnl[i]->ret;
		i++;
	}
	if (x == 0)
	{
		if (*gnl != NULL)
			free(*gnl);
		*gnl = NULL;
	}
	*line = NULL;
	return (0);
}
