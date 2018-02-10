#include "minishell.h"

static int	is_redir_simple(char *token)
{
	return (TRUE);
}

static int	is_redir_double(char *token)
{
	return (TRUE);
}

static int	is_redir_fd(char *token)
{
	return (TRUE);
}

static int	is_pipe(char *token)
{
	if (ft_strlen(token) == 1 && *token == '|')
		return (TRUE);
	return (FALSE);
}

static int	is_pipe_or_redir(char *token)
{
	if (is_pipe(token) == TRUE)
		return (TRUE);
	return (FALSE);
}

int			main(int ac, char **av)
{
	if (ac != 2)
		return (EXIT_SUCCESS);
	ft_putendl(is_pipe_or_redir(*(av + 1)) == TRUE ? "TRUE" : "FALSE");
	return (EXIT_SUCCESS);
}
