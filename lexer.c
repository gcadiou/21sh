/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 14:21:19 by gcadiou           #+#    #+#             */
/*   Updated: 2018/02/06 21:15:31 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header21sh.h"

char	*fill_stream(char **argv)
{
	int		x;
	char	*stream;

	x = 2;
	stream = ft_strdup(argv[1]);
	while (argv[x])
	{
		stream = ft_strjoin_separator(stream, argv[x], "  ", 1);
		x++;
	}
	return (stream);
}

int		next_token(int x, t_token *lexeme, char *stream)
{
	while (ISSPACE(stream[x]))
			x++;
	if (check_newline(&x, lexeme, stream) == 1)
		return (x);
	else if (check_operator(&x, lexeme, stream) == 1)
		return (x);
	else if (check_io_number(&x, lexeme, stream) == 1)
		return (x);
	else
	{
		while (NOSPACE(stream[x]))
			x++;
	}
	return (x);
}

int		main(int argc, char *argv[])
{
	t_token *lexeme;
	int		token_max;
	char	*stream;
	int		x;

	x = 0;
	if (argc < 2)
	{
		ft_putstr("no args");
		return (0);
	}
	token_max = 64;
	lexeme = malloc(sizeof(lexeme) * token_max);
	ft_bzero(lexeme, 64);
	stream = fill_stream(argv);
	while ((x = next_token(x, lexeme, stream)) != 0)
	{
		if (x == token_max - 1)
		{
			lexeme = ft_realloc(lexeme, token_max * 2, token_max);
			token_max *= 2;
		}
	}
	return 0;
}
