/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:56:38 by apedron           #+#    #+#             */
/*   Updated: 2018/02/09 18:56:23 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Display default shell prompt.
**	-------------------------------------------------------------------------- +
*/

void	sh_prompt(void)
{
	ft_putstr(C_RESET);
	ft_putstr(C_PROMPT);
	ft_putstr("$> ");
	ft_putstr(C_RESET);
}

/*
**	-------------------------------------------------------------------------- +
**	Display "quote-missing" shell prompt.
**	-------------------------------------------------------------------------- +
*/

void	sh_prompt_q(void)
{
	ft_putstr(C_RESET);
	ft_putstr("> ");
}

/*
**	-------------------------------------------------------------------------- +
**	On error, prints a message on standard error, and returns "EXIT_FAILURE".
**	eg. return (sh_return("error: invalid tty"))
**	-------------------------------------------------------------------------- +
*/

int		sh_return(char *message)
{
	char	*err;

	if (message)
	{
		if (!(err = ft_strjoin("21sh: error: ", message)))
			return (EXIT_FAILURE);
		ft_putendl_fd(err, STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}

/*
**	-------------------------------------------------------------------------- +
**	On error, prints a message on standard error, and exits with status
**	"EXIT_FAILURE".
**	eg. sh_exit("error: env_init() failed to execute")
**	-------------------------------------------------------------------------- +
*/

void	sh_exit(char *message)
{
	char	*err;

	if (message)
	{
		if (!(err = ft_strjoin("21sh: error: ", message)))
			exit(EXIT_FAILURE);
		ft_putendl_fd(err, STDERR_FILENO);
	}
	exit(EXIT_FAILURE);
}
