/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_substitute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 22:38:22 by apedron           #+#    #+#             */
/*   Updated: 2018/04/04 21:09:21 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles tilde substitution.
**	-------------------------------------------------------------------------- +
*/

static int	token_replace_tilde(t_token **head, t_token *node)
{
	char	*new_content;

	if (env_get_val("HOME"))
	{
		if (!(new_content = ft_strjoin(env_get_val("HOME"), node->content + 1)))
			return (EXIT_FAILURE);
		ft_strdel(&node->content);
		node->content = new_content;
	}
	else
	{
		ft_putendl_fd("21sh: error: can't substitute, $HOME not set",
				STDERR_FILENO);
		token_del_node(head, node);
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles status substitution.
**	-------------------------------------------------------------------------- +
*/

static int	token_replace_status(t_token *node)
{
	ft_strdel(&node->content);
	if (!(node->content = ft_itoa(g_status)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles environment variable substitution.
**	-------------------------------------------------------------------------- +
*/

static int	token_replace_env(t_token **head, t_token *node)
{
	extern char	**environ;
	int			i;
	int			n;

	i = 0;
	n = ft_strlen(node->content + 1);
	while (environ[i])
	{
		if (ft_strncmp(node->content + 1, environ[i], n) == 0
				&& environ[i][n] == '=')
		{
			ft_strdel(&node->content);
			if (!(node->content = ft_strdup(&(environ[i][n + 1]))))
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	token_del_node(head, node);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Substitutes tilde character (`~') and environment values (`$VAR').
**	-------------------------------------------------------------------------- +
*/

int			token_substitute(t_token **head)
{
	t_token		*node;

	node = *head;
	while (node)
	{
		if (node->type == TOKEN_WORD)
		{
			if (node->content[0] == '$')
			{
				if (ft_strcmp(node->content, "$?") == 0)
				{
					if (token_replace_status(node) == EXIT_FAILURE)
						return (EXIT_FAILURE);
				}
				else if (token_replace_env(head, node) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (ft_strcmp(node->content, "~") == 0 ||
						(node->content[0] == '~' && node->content[1] == '/'))
				if (token_replace_tilde(head, node) == EXIT_FAILURE)
					return (EXIT_FAILURE);
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
