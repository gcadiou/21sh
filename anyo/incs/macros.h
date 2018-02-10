/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 21:46:56 by apedron           #+#    #+#             */
/*   Updated: 2018/02/09 19:04:45 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
**	-------------------------------------------------------------------------- +
**	COMMON
**	-------------------------------------------------------------------------- +
*/

# define FALSE				0
# define TRUE				1
# define NONE				10
# define CURR				11

/*
**	-------------------------------------------------------------------------- +
**	TOKEN RECOGNITION
**	-------------------------------------------------------------------------- +
*/

# define IS_TOKEN_GREAT(s)		!ft_strcmp(s, ">") ? TRUE : FALSE
# define IS_TOKEN_PIPE(s)		!ft_strcmp(s, "|") ? TRUE : FALSE
# define IS_TOKEN_LESS(s)		!ft_strcmp(s, "<") ? TRUE : FALSE
# define IS_TOKEN_SEMICOLON(s)	!ft_strcmp(s, ";") ? TRUE : FALSE
# define IS_TOKEN_DLESS(s)		!ft_strcmp(s, "<<") ? TRUE : FALSE
# define IS_TOKEN_DGREAT(s)		!ft_strcmp(s, ">>") ? TRUE : FALSE
# define IS_TOKEN_LESSAND(s)	!ft_strcmp(s, "<&") ? TRUE : FALSE
# define IS_TOKEN_GREATAND(s)	!ft_strcmp(s, ">&") ? TRUE : FALSE
# define IS_TOKEN_AND_IF(s)		!ft_strcmp(s, "&&") ? TRUE : FALSE
# define IS_TOKEN_OR_IF(s)		!ft_strcmp(s, "||") ? TRUE : FALSE

/*
**	-------------------------------------------------------------------------- +
**	ESCAPE VALUES, CHARACTERS & KEY CODES
**	-------------------------------------------------------------------------- +
*/

# define C_PROMPT			"\033[38;5;46m"

# define ESC_RIGHT_ARROW	"\033[C"
# define ESC_LEFT_ARROW		"\033[D"
# define ESC_CLRSCR			"\033[J"
# define ESC_BACKSPACE		"\b \b"

# define CH_UP				'A'
# define CH_DOWN			'B'
# define CH_RIGHT			'C'
# define CH_LEFT			'D'
# define CH_END				'F'
# define CH_HOME			'H'
# define CH_SQUARE_BRACKET	'['

# define CH_SEMICOLON		';'
# define CH_SQUOTE			'\''
# define CH_DQUOTE			'\"'
# define CH_BACKSLASH		'\\'
# define CH_LINE_START		'\r'

# define KP_CTRL_C			-42
# define KP_CTRL_B			0x02
# define KP_CTRL_D			0x04
# define KP_CTRL_L			0x0c
# define KP_CTRL_S			0x13
# define KP_CTRL_V			0x16
# define KP_CTRL_X			0x18
# define KP_ESC				0x1b
# define KP_BACKSPACE		0x7f

#endif
