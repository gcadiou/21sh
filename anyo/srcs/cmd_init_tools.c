/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 16:54:56 by apedron           #+#    #+#             */
/*   Updated: 2018/02/01 10:51:59 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Helps handling quotes in all the above functions.
**	-------------------------------------------------------------------------- +
*/

static int	words_new_i(const char *raw_input, int i)
{
	char	c;

	c = 0;
	while (*(raw_input + i) && ft_isspace(*(raw_input + i)) == 0)
	{
		if (*(raw_input + i) == '\'' || *(raw_input + i) == '\"')
		{
			c = *(raw_input + i);
			i++;
			while (*(raw_input + i) && *(raw_input + i) != c)
				i++;
		}
		if (*(raw_input + i + 1) && ft_isspace(*(raw_input + i + 1)) == 1)
			break ;
		i++;
	}
	return (i);
}

/*
**	-------------------------------------------------------------------------- +
**	Counts & returns the number of words (tokens) in the string. It counts the
**	whole content between a couple of quotes as one word.
**	-------------------------------------------------------------------------- +
*/

int			words_count(const char *raw_input)
{
	int		counter;
	int		sw;
	int		i;

	i = 0;
	sw = 0;
	counter = 0;
	while (*(raw_input + i))
	{
		if (sw == 1 && ft_isspace(*(raw_input + i)) == 1)
			sw = 0;
		if (sw == 0 && ft_isspace(*(raw_input + i)) == 0)
		{
			sw = 1;
			i = words_new_i(raw_input, i);
			counter++;
		}
		if (!*(raw_input + i))
			break ;
		i++;
	}
	return (counter);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the index of the first character of the word (token) at the given
**	index in the string, or -1 if not found.
**	-------------------------------------------------------------------------- +
*/

int			words_first_c(const char *raw_input, int index)
{
	int		counter;
	int		sw;
	int		i;

	i = 0;
	sw = 0;
	counter = 0;
	while (*(raw_input + i))
	{
		if (sw == 1 && ft_isspace(*(raw_input + i)) == 1)
			sw = 0;
		if (sw == 0 && ft_isspace(*(raw_input + i)) == 0)
		{
			sw = 1;
			if (counter == index)
				return (i);
			i = words_new_i(raw_input, i);
			counter++;
		}
		i++;
	}
	return (-1);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the index of the last character of the word (token) at the given
**	index in the string, or -1 if not found.
**	-------------------------------------------------------------------------- +
*/

int			words_last_c(const char *raw_input, int index)
{
	int		counter;
	int		sw;
	int		i;

	i = 0;
	sw = 0;
	counter = 0;
	while (*(raw_input + i))
	{
		if (sw == 1 && ft_isspace(*(raw_input + i)) == 1)
			sw = 0;
		if (sw == 0 && ft_isspace(*(raw_input + i)) == 0)
		{
			sw = 1;
			i = words_new_i(raw_input, i);
			if (counter == index)
				return (*(raw_input + i) == 0 ? (i - 1) : i);
			counter++;
		}
		i++;
	}
	return (-1);
}
