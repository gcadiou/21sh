/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 12:39:55 by gcadiou           #+#    #+#             */
/*   Updated: 2018/02/07 13:53:53 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header21sh.h"

int		check_newline(int *x, int *y, t_token *lexeme, char *stream)
{
	if (stream[*y] == '\0')
		return (0);
	return (*x);
}

int		check_operator(int *x, int *y, t_token *lexeme, char *stream)
{
	int		i;

	i = *y;
	if (stream[i] == '&' && stream[i + 1] == '&')
		lexeme[*x].type = AND_IF;
	else if (stream[i] == '|' && stream[i + 1] == '|')
		lexeme[*x].type = OR_IF;
	else if (stream[i] == ';' && stream[i + 1] == ';')
		lexeme[*x].type = DSEMI;
	else if (stream[i] == '|' && stream[i + 1] == '<' && stream[i + 2] == '-')
		lexeme[*x].type = DLESSDASH;
	else if (stream[i] == '<' && stream[i + 1] == '<')
		lexeme[*x].type = DLESS;
	else if (stream[i] == '>' && stream[i + 1] == '>')
		lexeme[*x].type = DGREAT;
	else if (stream[i] == '<' && stream[i + 1] == '&')
		lexeme[*x].type = LESSAND;
	else if (stream[i] == '>' && stream[i + 1] == '&')
		lexeme[*x].type = GREATAND;
	else if (stream[i] == '<' && stream[i + 1] == '>')
		lexeme[*x].type = LESSGREAT;
	else if (stream[i] == '>' && stream[i + 1] == '|')
		lexeme[*x].type = CLOBBER;
	else
		return (*y);
	(*y)++;
	return (*y);
}

