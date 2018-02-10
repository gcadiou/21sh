/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:05:40 by apedron           #+#    #+#             */
/*   Updated: 2018/02/08 14:27:35 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Reverses the order of the linked list.
**	-------------------------------------------------------------------------- +
*/

void	env_reverse(t_env **head)
{
	t_env	*first;
	t_env	*rest;

	if (!(*head))
		return ;
	first = *head;
	rest = first->next;
	if (!rest)
		return ;
	env_reverse(&rest);
	first->next->next = first;
	first->next = NULL;
	*head = rest;
}

/*
**	-------------------------------------------------------------------------- +
**	Prints the linked list content, formatted as following: name=value.
**	-------------------------------------------------------------------------- +
*/

void	env_print(t_env *head)
{
	if (!head)
		return ;
	env_print(head->next);
	ft_putstr(head->name);
	ft_putstr("=");
	ft_putendl(head->value);
}

/*
**	-------------------------------------------------------------------------- +
**	Releases the memory of the linked list containing the environ.
**	-------------------------------------------------------------------------- +
*/

void	env_free(t_env **head)
{
	t_env	*node;
	t_env	*temp;

	node = *head;
	while (node)
	{
		ft_strdel(&node->name);
		ft_strdel(&node->value);
		temp = node;
		node = node->next;
		ft_free(temp);
	}
	ft_free(node);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the lenght of the given linked list.
**	-------------------------------------------------------------------------- +
*/

int		env_len(t_env **head)
{
	t_env	*node;
	int		len;

	len = 0;
	node = *head;
	while (node)
	{
		node = node->next;
		len++;
	}
	return (len);
}

/*
**	-------------------------------------------------------------------------- +
**	Takes the environ as a linked list, & returns it as an array of
**	char-pointers.
**	-------------------------------------------------------------------------- +
*/

char	**env_as_array(t_env **head)
{
	t_env	*node;
	char	**ret;
	char	*temp;
	int		len;
	int		i;

	i = 0;
	len = env_len(head);
	if (!(ret = ft_memalloc(sizeof(char *) * (len + 1))))
		return (NULL);
	node = *head;
	while (node)
	{
		if (!(temp = ft_strjoin(node->name, "=")))
			return (NULL);
		if (!(*(ret + i) = ft_strjoin(temp, node->value)))
			return (NULL);
		ft_strdel(&temp);
		node = node->next;
		i++;
	}
	*(ret + i) = NULL;
	ft_arrrev(ret);
	return (ret);
}
