/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header21sh.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 04:40:29 by gcadiou           #+#    #+#             */
/*   Updated: 2018/01/26 05:41:47 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER21SH_H
# define HEADER21SH_H

# include "Libft/libft.h"

typedef struct		s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

#endif
