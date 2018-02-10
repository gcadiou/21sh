/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:22:38 by apedron           #+#    #+#             */
/*   Updated: 2018/01/22 15:10:52 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_is_valid_pipe(char *command, int i)
{
	if (*(command + i) == '|')
		if (*(command + i - 1) && *(command + i + 1)
				&& *(command + i - 1) != '|' && *(command + i + 1) != '|')
			return (TRUE);
	return (FALSE);
}

static int	cmd_count_pipe(char **command)
{
	int	counter;
	int	x;
	int	i;

	i = 0;
	counter = 0;
	while (*(command + i))
	{
		x = 0;
		while (command[i][x])
			if (cmd_is_valid_pipe(*(command + i), x++) == TRUE)
				counter++;
		i++;
	}
	return (counter);
}

static char	**cmd_split_pipe(char **command)
{
	char	**ret;
	int		size;
	int		i;
	
	size = cmd_count_pipe(command);
	if (!(ret = ft_memalloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		if (!())
		i++;
	}
	*(ret + i) = NULL;
	return (ret);
}

int			cmd_execute(t_env **env, char **command)
{
	(void)env;
	ft_putarr(command);
	ft_putchar('\n');
	cmd_split_pipe(command);
	if (ft_strcmp(*command, "exit") == 0)
		exit(0);
	return (EXIT_SUCCESS);
}
