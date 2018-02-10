/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:35:41 by apedron           #+#    #+#             */
/*   Updated: 2018/02/10 23:42:27 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Returns, if existing, the value for a given `name` in the environ.
**	It does NOT return a copy of the string, but the original one.
**	-------------------------------------------------------------------------- +
*/

/* Old Version ---------------------------------------------------------------
char	*env_get_val(t_env **head, char *name)
{
	t_env	*node;

	node = *head;
	while (node)
	{
		if (ft_strcmp(node->name, name) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}
*/

char		*env_get_val(char *name)
{
	extern char	**environ;
	int			i;
	int			n;

	i = 0;
	n = ft_strlen(name);
	while (environ[i])
	{
		if ((ft_strncmp(name, environ[i], n) == 0 && environ[i][n + 1] == '='))
			return (&(environ[i][n + 1]));
		i++;
	}
	return (NULL);
}

/*
**	-------------------------------------------------------------------------- +
**	Checks if 'name' is already in the environ, or not.
**	-------------------------------------------------------------------------- +
*/

/* Old Version ---------------------------------------------------------------
int		env_entry_exists(t_env **head, char *name)
{
	t_env	*node;

	node = *head;
	while (node)
	{
		if (ft_strcmp(node->name, name) == 0)
			return (TRUE);
		node = node->next;
	}
	return (FALSE);
}
*/

int		env_entry_exists(char *name)
{
	extern char	**environ;
	int			i;
	int			n;

	i = 0;
	n = ft_strlen(name);
	while (environ[i])
	{
		if ((ft_strncmp(name, environ[i], n) == 0 && environ[i][n + 1] == '='))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/*
**	-------------------------------------------------------------------------- +
**	Replaces the value of 'name' with a new value in the environ.
**	-------------------------------------------------------------------------- +
*/

/* Old Version ---------------------------------------------------------------
int		env_replace(t_env **head, char *name, char *value)
{
	t_env	*node;

	node = *head;
	while (node)
	{
		if (ft_strcmp(node->name, name) == 0)
		{
			ft_strdel(&node->value);
			if (!(node->value = ft_strdup(value)))
				return (EXIT_FAILURE);
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
*/

/*
**----------------------------------------------------------------------------
** find the var corresponding, delete it,
** malloc a new string able to stock : "name" + '=' + "value" + '\0',
** then fill it with the given strings
*/

int			env_replace(char *name, char *value)
{
	extern char	**environ;
	int			i;
	int			n;

	i = 0;
	n = ft_strlen(name);
	while (environ[i])
	{
		if ((ft_strncmp(name, environ[i], n) == 0 && environ[i][n + 1] == '='))
		{
			ft_strdel(*(environ[i]));
			if (!(environ[i] = ft_memalloc(sizeof(char) *
							(n + 2 + ft_strlen(value)))))
				return (EXIT_FAILURE);
			ft_strcpy(environ[i], name);
			environ[i][n + 1] = '=';
			ft_strcpy(&(environ[i][n + 2]), value);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

/*
**	-------------------------------------------------------------------------- +
**	Appends the 'name'/'value' couple to the environ.
**	-------------------------------------------------------------------------- +
*/

/* Old Version ---------------------------------------------------------------
int		env_append(t_env **head, char *name, char *value)
{
	t_env	*node;

	if (env_entry_exists(head, name) == TRUE)
	{
		env_replace(head, name, value);
		return (EXIT_SUCCESS);
	}
	node = *head;
	while (node)
		node = node->next;
	if (!(node = ft_memalloc(sizeof(t_env))))
		return (EXIT_FAILURE);
	if (!(node->name = ft_strdup(name)))
		return (EXIT_FAILURE);
	if (!(node->value = ft_strdup(value)))
		return (EXIT_FAILURE);
	node->next = *head;
	*head = node;
	return (EXIT_SUCCESS);
}
*/

int			env_append(char *name, char *value)
{
	extern char	**environ;
	char		**tmp;
	int			i;
	int			n;

	if (env_replace(name, value) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (!(tmp = ft_narrdup(environ, 1)))
		return (EXIT_FAILURE);
	i = 0;
	while (tmp[i])
		i++;
	n = ft_strlen(name);
	if (!(tmp[i] = ft_memalloc(sizeof(char) *
					(n + 2 + ft_strlen(value)))))
		return (EXIT_FAILURE);
	ft_strcpy(tmp[i], name);
	tmp[i][n + 1] = '=';
	ft_strcpy(&(tmp[i][n + 2]), value);
	tmp[i + 1] = NULL;
	ft_arrfree(environ);
	environ = tmp;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Removes the element called 'name' in the environ.
**	-------------------------------------------------------------------------- +
*/

int		env_remove(t_env **head, char *name)
{
	t_env	*node;
	t_env	*save;

	if (ft_strcmp((*head)->name, name) == 0)
	{
		ft_strdel(&(*head)->name);
		ft_strdel(&(*head)->value);
		save = (*head)->next;
		ft_free(*head);
		*head = save;
	}
	node = *head;
	while (node)
	{
		if (node->next && ft_strcmp(node->next->name, name) == 0)
		{
			ft_strdel(&node->next->name);
			ft_strdel(&node->next->value);
			save = node->next->next;
			ft_free(node->next);
			node->next = save;
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}

int			env_remove(char *name)
{
	extern char	**environ;
	char		**tmp;
	int			i;
	int			n;
	int			l;

	if (!env_entry_exists(name) || environ == NULL)
		return (EXIT_SUCCESS);
	n = ft_arrlen(environ);
	if (!(tmp = ft_memalloc(sizeof(char *) * n)))
		return (EXIT_FAILURE);
	i = 0;
	l = 0;
	while (l < (n - 1))
	{
		if ((ft_strncmp(name, environ[i], n) == 0 && environ[i][n + 1] == '='))
		{
			i++;
			continue;
		}
		if (!(*(tmp + l) = ft_strdup(*(environ + i))))
			return (EXIT_FAILURE);
		i++;
		l++;
	}
	tmp[l] = NULL;
	ft_arrfree(environ);
	environ = tmp;
	return (EXIT_SUCCESS);
}
