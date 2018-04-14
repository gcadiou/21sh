/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcadiou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:14:07 by gcadiou           #+#    #+#             */
/*   Updated: 2018/04/02 21:25:17 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Change current directory and sets environment variables accordingly.
**	-------------------------------------------------------------------------- +
*/

static int	change_dir(char *curpath, char *tmp, int old)
{
	if (curpath[0] == '-' && curpath[1] == '\0' && (old = TRUE))
		if (!(curpath = env_get_val("OLDPWD")))
		{
			ft_putendl_fd("cd: error: can't get $OLDPWD", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	if (chdir(curpath) != 0)
	{
		ft_putstr_fd(access(curpath, F_OK) != -1 ? "cd: can't access: " :
				"cd: no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(curpath, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	old == TRUE ? ft_putendl_fd(curpath, STDOUT_FILENO) : 0;
	if (env_append("OLDPWD", env_get_val("PWD")) == EXIT_FAILURE)
		return (-1);
	if ((tmp = getcwd(NULL, 0)))
	{
		if (env_append("PWD", tmp) == EXIT_FAILURE)
			return (-1);
	}
	else if (env_append("PWD", curpath) == EXIT_FAILURE)
		return (-1);
	ft_strdel(&tmp);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Checks if $HOME is set and accessible.
**	-------------------------------------------------------------------------- +
*/

static char	*cd_check_home(void)
{
	char	*tmp;

	if (env_entry_exists("HOME") == -1)
	{
		ft_putendl_fd("cd: $HOME not set", STDERR_FILENO);
		return (NULL);
	}
	if (!(tmp = env_get_val("HOME")) || ft_strisblank(tmp) == TRUE)
	{
		ft_putendl_fd("cd: cannot find $HOME value", STDERR_FILENO);
		return (NULL);
	}
	else
		return (tmp);
}

/*
**	-------------------------------------------------------------------------- +
**	cd [directory]
**	Change the working directory.
**
**	Return -1, EXIT_SUCCESS or EXIT_FAILURE only.
**	-------------------------------------------------------------------------- +
*/

int			my_cd(char **args, int *status)
{
	char	*tmp;
	int		i;

	i = ft_arrlen(args);
	if (i == 1)
	{
		if (!(tmp = cd_check_home()))
			return ((*status = 0));
		return ((*status = change_dir(tmp, NULL, 0)));
	}
	else if (i >= 2)
		return ((*status = change_dir(args[1], NULL, 0)));
	return ((*status = 1));
}
