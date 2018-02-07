/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header21sh.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 04:40:29 by gcadiou           #+#    #+#             */
/*   Updated: 2018/02/07 13:30:38 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER21SH_H
# define HEADER21SH_H

# include "Libft/libft.h"

/*
 ** Tokens identifier
*/
# define TOKEN              1
# define WORD               2
# define ASSIGNEMENT_WORD   3
# define NAME               4
# define NEWLINE            5
# define IO_NUMBER          6
# define AND_IF             7
# define OR_IF              8
# define DSEMI              9
# define DLESS             10
# define DGREAT            11
# define LESSAND           12
# define GREATAND          13
# define LESSGREAT         14
# define DLESSDASH         15
# define CLOBBER            16

typedef struct		s_token
{
	int		type;
	int		value;
}					t_token;

typedef struct		s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

//int		check_newline(int *x, int *y, t_token *lexeme, char *stream);

int		check_newline(int *x, int *y, t_token *lexeme, char *stream);

int		check_operator(int *x, int *y, t_token *lexeme, char *stream);

int		check_io_number(int *x, int *y, t_token *lexeme, char *stream);

#endif
