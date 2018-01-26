/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:08:30 by gcadiou           #+#    #+#             */
/*   Updated: 2017/09/25 15:25:36 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1000

# include "libft.h"

typedef struct	s_gnl
{
	char	*str_new;
	char	*str_old;
	int		ret;
	int		notfirst;
	int		fd;
	int		last;
}				t_gnl;

int				old_to_new(t_gnl *gnl);
int				norme_old_to_new(t_gnl *gnl, int i, int i2);
int				norme_gnl(t_gnl *gnl, char **line, int act);
int				norme_gnl_free(t_gnl **gnl, char **line, int act);
int				get_next_line(const int fd, char **line);
#endif
