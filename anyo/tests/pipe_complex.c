#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* syntax: `cmd1 | cmd2 | cmd3 [ | cmd4 ...]`					*/
/* redirects the output of 'cmd1' to the input of 'cmd2', etc	*/

/* https://stackoverflow.com/a/8092270 */

static int	spawn_process(char ***cmd, char **path, char **env, int in, int out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != STDOUT_FILENO)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		return (execve(path[0], cmd[0], env));
	}
	return (pid);
}

static int	fork_pipes(char ***cmd, char **path, char **env, int n)
{
	int	fd[2];
	int	in;
	int	i;

	i = 0;
	in = STDIN_FILENO; /* first process should get its input from stdin */
	while (i < n - 1) /* last process must be executed outside the loop */
	{
		pipe(fd); /* see pipe_simple.c for description */
		if (spawn_process(cmd + i, path + i, env, in, fd[1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		close(fd[1]); /* no need for the write end of the pipe */
		in = fd[0]; /* keep the "read end" of the pipe, next child will read from it */
		i++;
	}
	/* set stdin as the "read end" of the previous pipe and output to stdout */
	if (in != STDIN_FILENO)
		dup2(in, STDIN_FILENO);
	return (execve(path[i], cmd[i], env));
}

int			main(int ac, char **av, char **env)
{
	char	*cmd1[] = { "ls", "-l", "-a", NULL };
	char	*cmd2[] = { "sort", NULL };
	char	*cmd3[] = { "wc", "-l", NULL };
	char	**cmd[] = { cmd1, cmd2, cmd3 };

	char	*path1 = "/bin/ls";
	char	*path2 = "/usr/bin/sort";
	char	*path3 = "/usr/bin/wc";
	char	*path[] = { path1, path2, path3, NULL };
	
	int		n;

	if (ac != 1)
		return (EXIT_FAILURE);
	n = sizeof(cmd) / sizeof(*cmd);
	return (fork_pipes(cmd, path, env, n) == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}
