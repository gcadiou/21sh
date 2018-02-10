#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* syntax: `cmd1 | cmd2`									*/
/* redirects the output of 'cmd1' to the input of 'cmd2'	*/

/* https://stackoverflow.com/a/2661833 */

static int	function(char **cmd1, char **cmd2, char *path1, char *path2, char **env)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	pipe(fd); /* opens the first 2 available fd, and stores them into fd[0] & fd[1] */
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		close(fd[1]); /* close write from child process */
		dup2(fd[0], STDIN_FILENO); /* replace stdin with the "read end" of the pipe */
		close(fd[0]); /* don't need another copy of the "read end" */
		if ((status = execve(path2, cmd2, env)) == -1)
			exit(status);
		kill(pid, SIGINT);
		exit(status);
	}
	else
	{
		close(fd[0]); /* close read from parent process */
		dup2(fd[1], STDOUT_FILENO); /* replace stdout with the "write end" of the pipe */
		close(fd[1]); /* don't need another copy of the "write end" */
		if ((status = execve(path1, cmd1, env)) == -1)
			exit(status);
		kill(pid, SIGINT);
		exit(status);
	}
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av, char **env)
{
	char	*cmd1[] = { "ls", "-l", "-a", NULL };
	char	*path1 = "/bin/ls";
	char	*cmd2[] = { "wc", "-c", NULL };
	char	*path2 = "/usr/bin/wc";

	if (ac != 1)
		return (EXIT_FAILURE);
	return (function(cmd1, cmd2, path1, path2, env));
}
