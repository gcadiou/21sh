/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 21:46:56 by apedron           #+#    #+#             */
/*   Updated: 2018/04/01 15:20:59 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
**	-------------------------------------------------------------------------- +
**	KEY CODES FOR DISPLAY
**	-------------------------------------------------------------------------- +
*/

# define KEY_NONE			0
# define KEY_BACKSPACE		1
# define KEY_CTRL_D			2
# define KEY_CTRL_L			3
# define KEY_END			4
# define KEY_HOME			5
# define KEY_DOWN_ARROW		6
# define KEY_UP_ARROW		7
# define KEY_LEFT_ARROW		8
# define KEY_RIGHT_ARROW	9
# define KEY_O_DOWN_ARROW	10
# define KEY_O_UP_ARROW		11
# define KEY_O_LEFT_ARROW	12
# define KEY_O_RIGHT_ARROW	13
# define KEY_CTRL_S			14
# define KEY_CTRL_V			15

/*
**	-------------------------------------------------------------------------- +
**	TOKEN VALUES
**	-------------------------------------------------------------------------- +
*/

# define TOKEN_NONE			0
# define TOKEN_BLANK		1
# define TOKEN_WORD			2
# define TOKEN_SQUOTED		3
# define TOKEN_DQUOTED		4
# define TOKEN_BS_QUOTED	5
# define TOKEN_IO_NUMBER	6
# define TOKEN_MINUS		7
# define TOKEN_GREAT 		8
# define TOKEN_LESS			9
# define TOKEN_DGREAT		10
# define TOKEN_DLESS		11
# define TOKEN_GREATAND		12
# define TOKEN_LESSAND		13
# define TOKEN_PIPE			14
# define TOKEN_AND_IF		15
# define TOKEN_OR_IF		16
# define TOKEN_SEMICOLON	17
# define TOKEN_EOL			18

/*
**	-------------------------------------------------------------------------- +
**	RETURN VALUES & MODES
**	-------------------------------------------------------------------------- +
*/

# define FALSE				0
# define TRUE				1
# define READ_END			0
# define WRITE_END			1
# define PROMPT_BASIC		0
# define PROMPT_QUOTE		1
# define INPUT_INIT			0
# define INPUT_RESET		1
# define EXIT_CTRL_C		2
# define TK_PREV			0
# define TK_NEXT			1
# define TERM_SAVE			0
# define TERM_RESET			1
# define RET_CTRL_C			0
# define RET_NEWLINE		1
# define REDIR_INIT			0
# define REDIR_RESET		1

/*
**	-------------------------------------------------------------------------- +
**	CHARACTERS, KEY & ESCAPE VALUES
**	-------------------------------------------------------------------------- +
*/

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
# define CH_BACKSPACE		"\b \b"

# define KP_ESC				0x1b
# define KP_CTRL_A			0x01
# define KP_CTRL_B			0x02
# define KP_CTRL_C			-42
# define KP_CTRL_D			0x04
# define KP_CTRL_E			0x05
# define KP_CTRL_L			0x0c
# define KP_CTRL_S			0x13
# define KP_CTRL_V			0x16
# define KP_CTRL_X			0x18
# define KP_BACKSPACE		0x7f

#endif
