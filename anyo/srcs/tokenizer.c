/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:58:24 by apedron           #+#    #+#             */
/*   Updated: 2018/02/09 19:04:54 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Temporary functions, to remove (here, and in tokenizer()).
**	-------------------------------------------------------------------------- +
*/

static void	token_print(t_token *head)
{
	t_token	*node;
	int		max_len;
	int		i;

	node = head;
	max_len = 0;
	while (node)
	{
		if ((int)ft_strlen(node->token) > max_len)
			max_len = ft_strlen(node->token);
		node = node->next;
	}
	node = head;
	while (node)
	{
		ft_putchar('(');
		ft_putstr(node->token);
		ft_putchar(')');
		i = 0;
		while (i++ <= max_len - (int)ft_strlen(node->token))
			ft_putchar(' ');
		ft_putstr(": ");
		ft_putendl(node->value);
		node = node->next;
	}
}

static void	token_free(t_token **head)
{
	t_token	*node;

	node = *head;
	while (node)
	{
		ft_strdel(&node->token);
		ft_strdel(&node->value);
		free(node);
		node = node->next;
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Token tools.
**	-------------------------------------------------------------------------- +
*/

int			token_is_operator_first_char(char fc)
{
	static char op_fc[] = { '>', '<', '|', '&', 0 };
	int			i;

	i = 0;
	while (op_fc[i])
		if (op_fc[i++] == fc)
			return (TRUE);
	return (FALSE);
}

int			token_is_operator(char *token)
{
	static char	*ops[] = {
	">", "<", "|", ">>", "<<", "<&", ">&", "&&", "||",
	NULL};
	int			i;

	i = 0;
	while (*(ops + i))
		if (ft_strcmp(token, *(ops + i++)) == 0)
			return (TRUE);
	return (FALSE);
}

static char	*get_token_value(char *token, char *value)
{
	if (value)
		return (ft_strdup(value));
	else if (IS_TOKEN_GREAT(token) == TRUE)
		return (ft_strdup("TOKEN_GREAT"));
	else if (IS_TOKEN_LESS(token) == TRUE)
		return (ft_strdup("TOKEN_LESS"));
	else if (IS_TOKEN_PIPE(token) == TRUE)
		return (ft_strdup("TOKEN_PIPE"));
	else if (IS_TOKEN_SEMICOLON(token) == TRUE)
		return (ft_strdup("TOKEN_SEMICOLON"));
	else if (IS_TOKEN_DGREAT(token) == TRUE)
		return (ft_strdup("TOKEN_DGREAT"));
	else if (IS_TOKEN_DLESS(token) == TRUE)
		return (ft_strdup("TOKEN_DLESS"));
	else if (IS_TOKEN_LESSAND(token) == TRUE)
		return (ft_strdup("TOKEN_LESSAND"));
	else if (IS_TOKEN_GREATAND(token) == TRUE)
		return (ft_strdup("TOKEN_GREATAND"));
	else if (IS_TOKEN_AND_IF(token) == TRUE)
		return (ft_strdup("TOKEN_AND_IF"));
	else if (IS_TOKEN_OR_IF(token) == TRUE)
		return (ft_strdup("TOKEN_OR_IF"));
	return (ft_strdup("TOKEN_WORD"));
}

int			token_add(t_token **head, char *token, char *value)
{
	t_token	*current;
	t_token	*new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (EXIT_FAILURE);
	if (!(new->token = ft_strdup(token)))
		return (EXIT_FAILURE);
	if (!(new->value = get_token_value(token, value)))
		return (EXIT_FAILURE);
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (EXIT_SUCCESS);
}

int			token_append(t_tokenizer *data, char ch)
{
	char	*token_new;

	if (data->token)
	{
		if (!(token_new = ft_strnew(ft_strlen(data->token) + 1)))
			return (EXIT_FAILURE);
		ft_strcpy(token_new, data->token);
		*(token_new + ft_strlen(data->token)) = ch;
		ft_strdel(&data->token);
	}
	else
	{
		if (!(token_new = ft_strnew(1)))
			return (EXIT_FAILURE);
		*token_new = ch;
	}
	data->token = token_new;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Token tools.
**	-------------------------------------------------------------------------- +
*/

static int	tokenizer_functions(t_token **head, t_tokenizer *data, char ch)
{
	static int	(*token_fct[])(t_token **, t_tokenizer *, char) = {
	token_process_1,
	token_process_2,
	token_process_3,
	token_process_4,
	token_process_5,
	token_process_6,
	token_process_7,
	token_process_8,
	token_process_9,
	token_process_10,
	NULL};
	int			ret;
	int			i;

	i = 0;
	while (token_fct[i] && (ret = token_fct[i](head, data, ch)) == 0)
		i++;
	return (ret);
}

int			tokenizer(char *input)
{
	t_tokenizer	data;
	t_token		*head;
	char		ch;
	int			ret;
	int			i;

	i = 0;
	head = NULL;
	data.token = NULL;
	data.sq = FALSE;
	data.dq = FALSE;
	data.bs = FALSE;
	data.op = FALSE;
	while (i <= (int)ft_strlen(input))
	{
		ch = *(input + i++);
		if ((ret = tokenizer_functions(&head, &data, ch)) == -1)
			return (EXIT_FAILURE);
		else if (ret == 2)
			break ;
	}
	token_print(head);
	token_free(&head);
	ft_strdel(&data.token);
	return (EXIT_SUCCESS);
}
