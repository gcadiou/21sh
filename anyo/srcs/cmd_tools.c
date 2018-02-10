/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:05:01 by apedron           #+#    #+#             */
/*   Updated: 2018/01/13 18:13:40 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Replace dots and dot-dots operators in the command line before processing
**	it, so it interpret them correctly. In some cases, getcwd() fails and the
**	operators can not be interpreted.
**	-------------------------------------------------------------------------- +
*/

static char	*replace_dot_dot(char *cmd)
{
	char	*prev_cwd;
	char	*cwd;
	char	*tmp;
	int		i;

	if (!(cwd = getcwd(NULL, 1024)))
	{
		ft_putendl_fd("21sh: can not interpret dot-dots.", STDERR_FILENO);
		return (cmd);
	}
	i = ft_strlen(cwd);
	while (i > 0 && *(cwd + i) != '/')
		i--;
	if (!(prev_cwd = ft_strndup(cwd, i)))
		return (NULL);
	ft_strdel(&cwd);
	if (!(tmp = ft_strdup(cmd + 2)))
		return (NULL);
	ft_strdel(&cmd);
	if (!(cmd = ft_strjoin_free(prev_cwd, tmp, 2)))
		return (NULL);
	return (cmd);
}

static char	*replace_dot(char *cmd)
{
	char	*cwd;
	char	*tmp;

	if (!(cwd = getcwd(NULL, 1024)))
	{
		ft_putendl_fd("21sh: can not interpret dots.", STDERR_FILENO);
		return (cmd);
	}
	if (!(tmp = ft_strdup(cmd + 1)))
		return (NULL);
	ft_strdel(&cmd);
	if (!(cmd = ft_strjoin_free(cwd, tmp, 2)))
		return (NULL);
	return (cmd);
}

char		**cmd_replace_dots(char **command)
{
	if (ft_strncmp(*(command + 0), "../", 3) == 0)
		if (!(*(command + 0) = replace_dot_dot(*(command + 0))))
			return (NULL);
	if (ft_strncmp(*(command + 0), "./", 2) == 0)
		if (!(*(command + 0) = replace_dot(*(command + 0))))
			return (NULL);
	return (command);
}

/*
**	-------------------------------------------------------------------------- +
**	Frees the linked list that contains command(s).
**	-------------------------------------------------------------------------- +
*/

void		cmd_free(t_cmd **head)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = *head;
	while (node)
	{
		ft_arrfree(node->command);
		temp = node;
		node = node->next;
		ft_free(temp);
	}
	ft_free(node);
}

/*
**	-------------------------------------------------------------------------- +
**	Reverses the linked list that contains command(s).
**	-------------------------------------------------------------------------- +
*/

void		cmd_reverse(t_cmd **head)
{
	t_cmd	*previous;
	t_cmd	*current;
	t_cmd	*next;

	next = NULL;
	current = *head;
	previous = NULL;
	while (current)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	*head = previous;
}
