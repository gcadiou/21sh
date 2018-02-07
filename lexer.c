/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 14:21:19 by gcadiou           #+#    #+#             */
/*   Updated: 2018/02/07 16:16:47 by gcadiou          ###   ########.fr       */
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

int		next_token(int x, int *y, t_token *lexeme, char *stream)
{
	while (ISSPACE(stream[*y]))
		(*y)++;
	if (check_newline(&x, y, lexeme, stream) == 1)
		return (0);
	else if (check_operator(&x, y, lexeme, stream) == 1)
		return (x);
//	else if (check_io_number(&x, y, lexeme, stream) == 1)
//		return (x);
	else
	{
		lexeme[x].type = TOKEN;
		while (NOSPACE(stream[*y]) && stream[*y] != '\0')
			(*y)++;
	}
	ft_putnbr(*y);
	ft_putendl("");
	return (x + 1);
}

int		main(int argc, char *argv[])
{
	t_token *lexeme;
	int		token_max;
	char	*stream;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (argc < 2)
	{
		ft_putstr("no args");
		return (0);
	}
	token_max = 64;
	lexeme = malloc(sizeof(lexeme) * token_max);
	ft_bzero(lexeme, 64);
	stream = fill_stream(argv);
	while ((x = next_token(x, &y, lexeme, stream)) != 0)
	{
		if (x == token_max - 1)
		{
			lexeme = ft_realloc(lexeme, token_max * 2, token_max);
			token_max *= 2;
		}
	}
	while (x < token_max)
	{
		ft_putnbr(lexeme[x].type);
		x++;
	}
	return 0;
}
