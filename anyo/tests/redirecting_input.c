#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

/* syntax: `cmd [fd]<word` (if 'fd' is not specified, 'fd' is `stdin`)	*/
/* redirects data from 'word' to 'fd' for 'cmd'							*/

/* http://www.sarathlakshman.com/2012/09/24/implementation-overview-of-redirection-and-pipe-operators-in-shell */
/* http://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_07	*/
/* https://git.kernel.org/pub/scm/utils/dash/dash.git/plain/src/redir.c?id=HEAD			*/
/* http://wiki.bash-hackers.org/syntax/redirection										*/
/* https://brendanzagaeski.appspot.com/000b.html										*/

static int	function(char **cmd, char **env, char *path, char *file)
{
	int		status;
	pid_t	pid;

	if (close(STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	if (open(file, O_RDONLY) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		if ((status = execve(path, cmd, env)) == -1)
			exit(status);
		kill(pid, SIGINT);
		exit(status);
	}
	else if (waitpid(pid, &status, 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int			main(int ac, char **av, char **env)
{
	char	*cmd[] = { "cat", "-e", NULL };
	char	*path = "/bin/cat";
	char	*file = "in.txt";

	if (ac != 1)
		return (EXIT_FAILURE);
	return (function(cmd, env, path, file));
}
