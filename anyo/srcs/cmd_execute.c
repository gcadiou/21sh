/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:15:22 by apedron           #+#    #+#             */
/*   Updated: 2018/01/30 15:38:18 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Executes the given program with its options, in the current environment.
**	-------------------------------------------------------------------------- +
*/

static int	exe_cute(char **environ, char **command, char *cmd_name, char *path)
{
	int		status;
	pid_t	pid;

	pid = fork();
	signal_handler(1);
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		if ((status = execve(path, command, environ)) == -1)
		{
			ft_putstr_fd("21sh: can't execute the program: ", STDERR_FILENO);
			ft_putendl_fd(cmd_name, STDERR_FILENO);
			exit(status);
		}
		kill(pid, SIGINT);
		exit(status);
	}
	else if (waitpid(pid, &status, 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Splits the environment variable 'PATH', and tries to find a matching path
**	for the called program.
**	-------------------------------------------------------------------------- +
*/

static int	get_cmd_path(t_env **env, char **cmd_path, char *cmd_name)
{
	char	**path_arr;
	char	*tmp;
	int		i;

	i = 0;
	if (!(path_arr = ft_strsplit(env_get_val(env, "PATH"), ':')))
		return (EXIT_FAILURE);
	while (*(path_arr + i))
	{
		if (!(tmp = ft_strjoin(*(path_arr + i), "/")))
			return (EXIT_FAILURE);
		if (!(*cmd_path = ft_strjoin_free(tmp, cmd_name, 1)))
			return (EXIT_FAILURE);
		if (access(*cmd_path, F_OK) == 0)
		{
			ft_arrfree(path_arr);
			return (EXIT_SUCCESS);
		}
		ft_strdel(&*cmd_path);
		i++;
	}
	ft_arrfree(path_arr);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the full path for a program, or outputs an accurate error message
**	and set the path to 'NULL'.
**	-------------------------------------------------------------------------- +
*/

static int	get_full_path(t_env **env, char **path, char *name, char *cmd)
{
	if (*cmd == '/')
	{
		if (access(cmd, F_OK) == -1)
		{
			ft_putstr_fd("21sh: ", STDERR_FILENO);
			ft_putstr_fd(name, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}
		else if (access(cmd, X_OK) == -1)
		{
			ft_putstr_fd("21sh: ", STDERR_FILENO);
			ft_putstr_fd(name, STDERR_FILENO);
			ft_putendl_fd(": permission denied", STDERR_FILENO);
		}
		else if (!(*path = ft_strdup(cmd)))
			return (EXIT_FAILURE);
	}
	else
	{
		if (!env_get_val(env, "PATH"))
			*path = NULL;
		else if (get_cmd_path(env, path, name) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (!*path)
		{
			ft_putstr_fd("21sh: ", STDERR_FILENO);
			ft_putstr_fd(name, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}
		else if (access(*path, X_OK) == -1)
		{
			ft_putstr_fd("21sh: ", STDERR_FILENO);
			ft_putstr_fd(name, STDERR_FILENO);
			ft_putendl_fd(": permission denied", STDERR_FILENO);
			ft_strdel(&*path);
		}
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Converts the environ, gets the binary's full path, and tries to execute it.
**	-------------------------------------------------------------------------- +
*/

static int	my_interpreter(t_env **env, char **command)
{
	char	**environ;
	char	*cmd_name;
	char	*cmd_path;

	cmd_path = NULL;
	if (!(cmd_name = ft_strdup(*(command + 0))))
		return (-1);
	if (!(command = cmd_replace_dots(command)))
		return (-1);
	if (!(environ = env_as_array(env)))
		return (-1);
	if (get_full_path(env, &cmd_path, cmd_name, *(command + 0)) == EXIT_FAILURE)
		return (-1);
	if (cmd_path != NULL)
		if (exe_cute(environ, command, cmd_name, cmd_path) == EXIT_FAILURE)
			return (-1);
	ft_strdel(&cmd_path);
	ft_strdel(&cmd_name);
	ft_arrfree(environ);
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Executes the entered command. Custom builtins can be added as functions,
**	but it must return specific values:
**	-1 on error, 0 if not the called builtin, 1 on successful execution.
**	-------------------------------------------------------------------------- +
*/

int			cmd_execute(t_env **env, char **command)
{
	static int	(*builtins[])(t_env **, char **) = {
	&my_echo,
	&my_cd,
	&my_setenv,
	&my_unsetenv,
	&my_env,
	&my_exit,
	&my_interpreter,
	NULL};
	int			ret;
	int			i;

	i = 0;
	ret = 0;
	while (builtins[i] && (ret = builtins[i](env, command)) == 0)
		i++;
	return (ret == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}
