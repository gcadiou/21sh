/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 11:03:25 by apedron           #+#    #+#             */
/*   Updated: 2017/12/18 11:06:43 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	format_curpath() formats `curpath` according to POSIX man of utility `cd`.
**
**		Summary of the POSIX man:
**	Copies the content of curpath, but without the following:
**		>	dot (".") + slashes that separate them from the next component
**		>	dot-dot ("..") if it has a preceding component != root or dot-dot
**		>	any trailing slash characters that are not also leading slashes,
**			replacing multiple non-leading con-secutive slashes with a single
**			slash, and replacing 3 or more leading slashes with a single slash.
**	If, as a result of this canonicalization, the curpath variable is null,
**	no further steps shall be taken.
**	-------------------------------------------------------------------------- +
*/

static int	format_check(char **arrpath, int i)
{
	if (ft_strcmp(*(arrpath + i), ".") == 0)
		return (FALSE);
	if (*(arrpath + (i + 1)) &&
		ft_strcmp(*(arrpath + i), "/") != 0 &&
		ft_strcmp(*(arrpath + i), "..") != 0 &&
		ft_strcmp(*(arrpath + (i + 1)), "..") == 0)
		return (FALSE);
	if (i > 0 && *(arrpath + (i - 1)) &&
		ft_strcmp(*(arrpath + i), "..") == 0 &&
		ft_strcmp(*(arrpath + (i - 1)), "/") != 0 &&
		ft_strcmp(*(arrpath + (i - 1)), "..") != 0)
		return (FALSE);
	return (TRUE);
}

char		*format_curpath(char *curpath)
{
	char	**arrpath;
	char	*tmp;
	int		i;

	i = 0;
	if (!(arrpath = ft_strsplit(curpath, '/')))
		return (NULL);
	ft_strdel(&curpath);
	if (!(curpath = ft_strdup("/")))
		return (NULL);
	while (*(arrpath + i))
	{
		if (format_check(arrpath, i) == TRUE)
		{
			if (!(tmp = ft_strjoin_free(curpath, *(arrpath + i), 1)))
				return (NULL);
			if (!(curpath = ft_strjoin_free(tmp, "/", 1)))
				return (NULL);
		}
		i++;
	}
	ft_arrfree(arrpath);
	return (curpath);
}
