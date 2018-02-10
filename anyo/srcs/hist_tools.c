/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:18:49 by apedron           #+#    #+#             */
/*   Updated: 2018/02/08 14:45:51 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Prints command history content.
**	-------------------------------------------------------------------------- +
*/

void	hist_output(t_hist *head)
{
	t_hist	*node;

	node = head;
	ft_putstr(FG_YELLOW);
	ft_putendl("--- + command history + ---");
	while (node)
	{
		ft_putstr(node->line);
		ft_putstr(" : ");
		ft_putendl(node->status == CURR ? "CURR" : "NONE");
		node = node->next;
	}
	ft_putendl("--- + command history + ---");
	ft_putstr(FG_RESET);
}

/*
**	-------------------------------------------------------------------------- +
**	Sets all status to 'NONE' after a command has been validated.
**	-------------------------------------------------------------------------- +
*/

void	hist_reset(t_hist **head)
{
	t_hist	*node;

	node = *head;
	while (node)
	{
		node->status = NONE;
		node = node->next;
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the last node of the command history linked list, or the node
**	preceding the node with status 'CURR'.
**	-------------------------------------------------------------------------- +
*/

t_hist	*hist_getpoc(t_hist **head)
{
	t_hist	*node;

	if (!*head)
		return (NULL);
	if ((*head)->status == CURR)
		return (*head);
	node = *head;
	while (node->next)
	{
		if (node->next->status == CURR)
		{
			node->next->status = NONE;
			break ;
		}
		node = node->next;
	}
	node->status = CURR;
	return (node);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the node after the one with status 'CURR'
**	-------------------------------------------------------------------------- +
*/

t_hist	*hist_getnoc(t_hist **head)
{
	t_hist	*node;

	if (!*head)
		return (NULL);
	node = *head;
	while (node->next)
	{
		if (node->status == CURR)
		{
			node->status = NONE;
			node = node->next;
			node->status = CURR;
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

/*
**	-------------------------------------------------------------------------- +
**	Appends new command (& related data) to the command history linked list.
**	-------------------------------------------------------------------------- +
*/

int		hist_append(t_hist **head, char *input)
{
	t_hist	*current;
	t_hist	*new;

	if (ft_strisblank(input) == TRUE)
		return (EXIT_SUCCESS);
	if (!(new = ft_memalloc(sizeof(t_hist))))
		return (EXIT_FAILURE);
	if (!(new->line = *(input + (ft_strlen(input) - 1)) == '\n' ?
			ft_strndup(input, ft_strlen(input) - 1) : ft_strdup(input)))
		return (EXIT_FAILURE);
	new->status = NONE;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		if (ft_strcmp(current->line, new->line) == 0)
		{
			ft_strdel(&new->line);
			free(new);
			return (EXIT_SUCCESS);
		}
		current->next = new;
	}
	return (EXIT_SUCCESS);
}
