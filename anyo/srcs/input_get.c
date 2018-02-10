/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:31:49 by apedron           #+#    #+#             */
/*   Updated: 2018/02/09 19:48:13 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Check if the given array of char pointers contains only blank characters.
**	-------------------------------------------------------------------------- +
*/

int			is_command_empty(char **command)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	if (!command || ft_arrlen(command) == 0)
		return (TRUE);
	else
	{
		while (*(command + i))
		{
			if (ft_strisblank(*(command + i)) == TRUE)
				counter++;
			i++;
		}
		return (counter == i ? TRUE : FALSE);
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Iterates through the input.
**	When it matches an opening quote (single or double), it tries to find the
**	closing one. If not found, it returns 0 which means the user needs to input
**	a new one.
**	-------------------------------------------------------------------------- +
*/

static int	is_quoted(const char *input, int index)
{
	if (!*(input + index - 1) || *(input + index - 1) != CH_BACKSLASH)
		return (FALSE);
	return (TRUE);
}

int			check_quotes(const char *input)
{
	char	c;
	int		i;

	i = 0;
	c = 0;
	while (*(input + i))
	{
		if (is_quoted(input, i) == TRUE)
			;
		else if (*(input + i) == CH_SQUOTE || *(input + i) == CH_DQUOTE)
		{
			c = *(input + i++);
			while (*(input + i) && (*(input + i) != c || (c == CH_DQUOTE && is_quoted(input, i) == TRUE)))
				i++;
			if (!*(input + i) || *(input + i) != c)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/*
**	-------------------------------------------------------------------------- +
**	If the last character of the string is a backslash - which means it has no
**	following character - the user needs to input at least one new character.
**	-------------------------------------------------------------------------- +
*/

static int	check_backslash(const char *input)
{
	if (*(input + (ft_strlen(input) - 1)) == CH_BACKSLASH)
		return (FALSE);
	return (TRUE);
}

/*
**	-------------------------------------------------------------------------- +
**	Asks the user for an input. If the quote formatting is not correct,
**	it will ask the user again to complete the string until it is correct.
**	-------------------------------------------------------------------------- +
*/

int			input_get(char **input)
{
	char	*temp;
	char	*new;

	sh_prompt();
	if (input_read(input, 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (check_quotes(*input) == FALSE || check_backslash(*input) == FALSE)
	{
		sh_prompt_q();
		if (input_read(&new, 2) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (!(temp = ft_strjoin_free(*input, "\n", 1)))
			return (EXIT_FAILURE);
		if (!(*input = ft_strjoin_free(temp, new, 2)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
