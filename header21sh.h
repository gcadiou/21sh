/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header21sh.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 04:40:29 by gcadiou           #+#    #+#             */
/*   Updated: 2018/02/06 21:15:32 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER21SH_H
# define HEADER21SH_H

# include "Libft/libft.h"

/*
 ** Tokens identifier
*/
# define TOKEN
# define WORD
# define ASSIGNEMENT_WORD
# define NAME
# define NEWLINE
# define IO_NUMBER
# define AND_IF
# define OR_IF
# define DSEMI
# define DLESS
# define DGREAT
# define LESSAND
# define GREATAND
# define LESSGREAT
# define DLESSDASH

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

#endif
