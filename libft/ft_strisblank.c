/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisblank.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:38:15 by apedron           #+#    #+#             */
/*   Updated: 2018/02/13 16:43:55 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Iterates over the given string, and checks if it is composed of blank
**	(as defined in ft_isspace()) characters only.
**	-------------------------------------------------------------------------- +
*/

int	ft_strisblank(char *str)
{
	size_t	counter;
	int		i;

	i = 0;
	counter = 0;
	if (!str || ft_strlen(str) == 0)
		return (1);
	while (*(str + i))
		if (ft_isspace(*(str + i++)) == 1)
			counter++;
	return (counter == ft_strlen(str) ? 1 : 0);
}
