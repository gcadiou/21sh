/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 19:36:11 by apedron           #+#    #+#             */
/*   Updated: 2018/01/13 18:10:26 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Checks if a semicolon (`;') is in between two quotes, or not. Returns 1 if
**	the semicolon must be considered as a delimiter, and therefore used to
**	split the string, 0 else.
**	-------------------------------------------------------------------------- +
*/

static int	is_a_delimiter(const char *str, int index)
{
	char	*tmp;
	int		ret;

	if (*(str + index) != ';')
		return (0);
	if (!(tmp = ft_strndup(str, index)))
		return (-1);
	ret = check_quotes(tmp);
	ft_strdel(&tmp);
	return (ret);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the number of words (tokens) in the given string, using a semicolon
**	(`;') as a delimiter, except those not considered as one.
**	Returns -2 on error, so the following malloc() fails.
**	-------------------------------------------------------------------------- +
*/

static int	get_nb_of_words(char const *str)
{
	int	counter;
	int	ret;
	int	sw;
	int	i;

	i = 0;
	sw = 0;
	counter = 0;
	while (*(str + i))
	{
		if (sw == 1 && (ret = is_a_delimiter(str, i)) == 1)
			sw = 0;
		if (sw == 0 && (ret = is_a_delimiter(str, i)) == 0)
		{
			sw = 1;
			counter++;
		}
		if (ret == -1)
			return (-2);
		i++;
	}
	return (counter);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the lenght of a string between two delimiters, or -2 on error, so
**	the following call to malloc() fails.
**	-------------------------------------------------------------------------- +
*/

static int	get_word_len(char const *str)
{
	int	len;
	int	ret;
	int	i;

	i = 0;
	len = 0;
	while (*(str + i) && (ret = is_a_delimiter(str, i)) == 1)
	{
		if (ret == -1)
			return (-2);
		i++;
	}
	while (*(str + i) && (ret = is_a_delimiter(str, i)) == 0)
	{
		if (ret == -1)
			return (-2);
		len++;
		i++;
	}
	return (len);
}

/*
**	-------------------------------------------------------------------------- +
**	Splits the input command, considering semicolons (`;') as delimiters,
**	except those in between quotes.
**	-------------------------------------------------------------------------- +
*/

char		**cmd_split(char const *str)
{
	char	**ret;
	int		i;
	int		j;
	int		k;

	j = 0;
	i = 0;
	if (!str || !(ret = ft_memalloc(sizeof(char *) *
			(get_nb_of_words(str) + 1))))
		return (NULL);
	while (i < get_nb_of_words(str))
	{
		k = 0;
		if (!(*(ret + i) = ft_strnew(get_word_len(&str[j]))))
			return (NULL);
		while (*(str + j) && is_a_delimiter(str, j) == 1)
			j++;
		while (*(str + j) && is_a_delimiter(str, j) == 0)
			ret[i][k++] = *(str + j++);
		ret[i][k] = '\0';
		i++;
	}
	*(ret + i) = NULL;
	return (ret);
}
