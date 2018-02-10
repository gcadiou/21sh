/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 19:33:16 by apedron           #+#    #+#             */
/*   Updated: 2018/01/30 16:03:09 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Returns the target of the command, removing the options.
**	-------------------------------------------------------------------------- +
*/

static char	*define_target(t_env **env, char **command)
{
	if (!*(command + 1))
		return (ft_strdup(env_get_val(env, "HOME")));
	else if (ft_strcmp(*(command + 1), "-") == 0)
		return (ft_strdup(env_get_val(env, "OLDPWD")));
	else if (ft_strcmp(*(command + 1), "-L") == 0 ||
				ft_strcmp(*(command + 1), "-P") == 0)
	{
		if (!*(command + 2))
			return (ft_strdup(env_get_val(env, "HOME")));
		else if (ft_strcmp(*(command + 2), "-") == 0)
			return (ft_strdup(env_get_val(env, "OLDPWD")));
		else
			return (ft_strdup(*(command + 2)));
	}
	else
		return (ft_strdup(*(command + 1)));
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the final target of the command.
**	-------------------------------------------------------------------------- +
*/

static char	*define_curpath(t_env **env, char **command)
{
	char	*target;
	char	*cwd;
	char	*tmp;

	if (!(target = define_target(env, command)))
		return (NULL);
	if (ft_strncmp(target, "/", 1) == 0)
		return (target);
	else
	{
		if (!(cwd = getcwd(NULL, 1024)))
		{
			ft_strdel(&target);
			return (NULL);
		}
		if (!(tmp = ft_strjoin_free(cwd, "/", 1)))
			return (NULL);
		return (ft_strjoin_free(tmp, target, 2));
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Tries to perform chdir() to 'curpath'.
**	-------------------------------------------------------------------------- +
*/

static int	change_curpath(t_env **env, char **command, char *curpath)
{
	char	*oldpwd;
	char	*pwd;

	if (chdir(curpath) == 0)
	{
		if (!(oldpwd = ft_strdup(env_get_val(env, "PWD"))))
			return (-1);
		if (*(command + 1) && ((ft_strcmp(*(command + 1), "-") == 0) ||
				(*(command + 2) && ft_strcmp(*(command + 2), "-") == 0)))
			ft_putendl(env_get_val(env, "OLDPWD"));
		if (!(pwd = getcwd(NULL, 1024)))
			env_replace(env, "PWD", "");
		else
		{
			env_replace(env, "PWD", pwd);
			env_replace(env, "OLDPWD", oldpwd);
		}
		ft_strdel(&oldpwd);
		ft_strdel(&pwd);
	}
	else
		return (-1);
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Uses errno to print accurate error message for my_cd().
**	-------------------------------------------------------------------------- +
*/

static int	my_error_msgs(t_env **env, char **command, int err)
{
	char	*target;

	if (err == 1337)
	{
		ft_putendl_fd("21sh: cd: set HOME, PWD & OLDPWD first", STDERR_FILENO);
		return (1);
	}
	if (!(target = define_target(env, command)))
		return (-1);
	if (err == EACCES)
	{
		ft_putstr_fd("21sh: cd: ", STDERR_FILENO);
		ft_putstr_fd(target, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else if (err == ENOENT)
	{
		ft_putstr_fd("21sh: cd: ", STDERR_FILENO);
		ft_putstr_fd(target, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	else
		return (-1);
	ft_strdel(&target);
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Implementation of the builtin `cd`.
**	-------------------------------------------------------------------------- +
*/

int			my_cd(t_env **env, char **command)
{
	char	*curpath;

	if (ft_strncmp(*(command + 0), "cd\0", 3) != 0)
		return (0);
	if (!(env_get_val(env, "PWD")) ||
		!(env_get_val(env, "HOME")) ||
		!(env_get_val(env, "OLDPWD")))
		return (my_error_msgs(env, command, 1337));
	if (!(curpath = define_curpath(env, command)))
		return (my_error_msgs(env, command, (int)errno));
	if (change_curpath(env, command, curpath) == -1)
	{
		ft_strdel(&curpath);
		return (my_error_msgs(env, command, (int)errno));
	}
	ft_strdel(&curpath);
	return (1);
}
