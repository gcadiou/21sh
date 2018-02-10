#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

/* syntax: `cmd [fd]<&word` (if 'fd' is not specified, 'fd' is `stdin`)				*/
/* syntax: `cmd [fd]>&word` (if 'fd' is not specified, 'fd' is `stdout`)			*/

/* redirects (dup) the output of 'cmd' that originally goes to fd 'fd' to fd 'word'	*/

/* if 'word' does not represent a fd already open for input, an error shall result	*/
/* if 'word' evaluates to '-', file descriptor 'fd' shall be closed					*/
/* if 'word' evaluates to something else, the behavior is unspecified				*/
/* attempts to close a fd that is not open shall not constitute an error			*/

/* http://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_07 */
/* https://brendanzagaeski.appspot.com/000b.html									  */
/* http://wiki.bash-hackers.org/syntax/redirection									  */

static int	function(char **cmd, char **env, char *path)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		close(STDERR_FILENO);
		dup(STDOUT_FILENO);
		if ((status = execve(path, cmd, env)) == -1)
			exit(status);
		kill(pid, SIGINT);
		exit(status);
	}
	else if (waitpid(pid, &status, 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av, char **env)
{
	char	*cmd[] = { "ls", "unknown_file", NULL };
	char	*path = "/bin/ls";

	if (ac != 1)
		return (EXIT_FAILURE);
	return (function(cmd, env, path)); /* `ls unknown_file 2<&1` */
}
