/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 12:01:17 by apedron           #+#    #+#             */
/*   Updated: 2018/02/09 18:35:14 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Check if current tty is valid, in order to make sure there will be no
**	problem with termcaps.
**	-------------------------------------------------------------------------- +
*/

static int	tty_check(void)
{
	char	*term_name;
	char	bp[1024];
	int		ret;

	if (!(term_name = getenv("TERM")))
		return (sh_return("TERM not set"));
	if (!isatty(STDIN_FILENO))
		return (sh_return("terminal type device is not valid"));
	if ((ret = tgetent(bp, term_name)) < 1)
	{
		if (ret == 0)
			return (sh_return("no such entry for current terminal type"));
		else if (ret == -1)
			return (sh_return("terminfo database could not be found"));
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Everything (almost) starts & dies here.
**	-------------------------------------------------------------------------- +
*/

int			main(void)
{
	char	*input;
	t_env	*env;

	if (tty_check() == EXIT_FAILURE)
		sh_exit("tty_check() failed somewhere");
	if (env_init(&env) == EXIT_FAILURE)
		sh_exit("env_init() failed somewhere");
	while (TRUE)
	{
		signal_handler(0);
		if (input_get(&input) == EXIT_FAILURE)
			sh_exit("input_get() failed somewhere");
		/* EXIT TEMPORAIRE */
		if (ft_strcmp(input, "exit") == 0)
			exit(EXIT_SUCCESS);
		/* "analyse lexicale" decoupe l'input en TOKENS */
		if (tokenizer(input) == EXIT_FAILURE)
			sh_exit("tokenizer() failed somewhere");
		/* (to do) "analyse semantique" verifier la grammaire des TOKENS */
		/* (to do) "arbre de syntaxe abstraite" etablir la sequence d'execution */
		/* (to do) execution
		t_cmd	*cmd;
		t_cmd	*mem;
		if (ft_strisblank(input) == FALSE)
		{
			if (cmd_init(&cmd, &env, input) == EXIT_FAILURE)
				exit(EXIT_FAILURE);
			mem = cmd;
			while (cmd)
			{
				if (is_command_empty(cmd->command) == FALSE)
					if (cmd_execute(&env, cmd->command) == EXIT_FAILURE)
						exit(EXIT_FAILURE);
				cmd = cmd->next;
			}
			cmd_free(&mem);
		}*/
		ft_strdel(&input);
	}
	exit(EXIT_SUCCESS);
}
