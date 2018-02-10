/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:23:56 by apedron           #+#    #+#             */
/*   Updated: 2018/02/10 22:42:24 by gcadiou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Adds 1 to the SHLVL entry in the environ.
**	-------------------------------------------------------------------------- +
*/

static int	env_shlvl_up(t_env *node)
{
	char	*new_value;

	if (ft_strncmp(node->name, "SHLVL\0", 6) != 0)
		return (EXIT_SUCCESS);
	if (!(new_value = ft_itoa(ft_atoi(node->value) + 1)))
		return (EXIT_FAILURE);
	ft_strdel(&node->value);
	if (!(node->value = ft_strdup(new_value)))
		return (EXIT_FAILURE);
	ft_strdel(&new_value);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns a copy of the value of the given environ entry.
**	-------------------------------------------------------------------------- +
*/

/* Old Version ---------------------------------------------------------------
static char	*env_dup_value(const char *entry)
{
	char	*ret;
	int		i;

	i = 0;
	if (!entry)
		return (NULL);
	while (*(entry + i) != '=')
		i++;
	if (!(ret = ft_strnew(ft_strlen(entry) - i - 1)))
		return (NULL);
	return (ft_strrcpy(ret, entry, i + 1));
}
*/

/*
**	-------------------------------------------------------------------------- +
**	Returns a copy of the name of the given environ entry.
**	-------------------------------------------------------------------------- +
*/

/* Old Version ---------------------------------------------------------------
static char	*env_dup_name(const char *entry)
{
	char	*ret;
	int		i;

	i = 0;
	if (!entry)
		return (NULL);
	while (*(entry + i) != '=')
		i++;
	if (!(ret = ft_strnew(i)))
		return (NULL);
	return (ft_strncpy(ret, entry, i));
}
*/

/*
**	-------------------------------------------------------------------------- +
**	Copies all the environ content (names & values) into a linked list,
**	and increases SHLVL by one.
**	Also, if the original environ does not contain a PATH entry, it adds one
**	with the default value "/bin:/usr/bin", as csh(1) does.
**	-------------------------------------------------------------------------- +
*/

/* Old version ---------------------------------------------------------------
int			env_init(t_env **head)
{
	extern char	**environ;
	t_env		*node;
	int			i;

	i = 0;
	while (*(environ + i))
	{
		if (!(node = ft_memalloc(sizeof(t_env))))
			return (EXIT_FAILURE);
		if (!(node->name = env_dup_name(*(environ + i))))
			return (EXIT_FAILURE);
		if (!(node->value = env_dup_value(*(environ + i))))
			return (EXIT_FAILURE);
		if (env_shlvl_up(node) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		node->next = *head;
		*head = node;
		i++;
	}
	// set default env variable if not set here, as sh does (PATH, TERM, PWD)
	return (EXIT_SUCCESS);
}
*/

int			env_init(void)
{
	extern char	**environ;

	if (!(environ = ft_arrdup(environ)))
		return (EXIT_FAILURE);
	env_shlvl_up(environ);
	return (EXIT_SUCCESS);
}
