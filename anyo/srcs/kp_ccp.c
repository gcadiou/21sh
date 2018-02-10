/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kp_ccp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:15:54 by apedron           #+#    #+#             */
/*   Updated: 2018/02/08 15:10:36 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*g_clipboard;

/*
**	-------------------------------------------------------------------------- +
**	Inserts the clipboard into 'input->line', at the cursor position.
**	-------------------------------------------------------------------------- +
*/

static char	*input_insert(t_line **input, char *str)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*ret;

	if (!(str1 = ft_strsub((*input)->line, 0, (*input)->cur_pos)))
		return (NULL);
	if (!(str2 = ft_strjoin_free(str1, str, 1)))
		return (NULL);
	if (!(str3 = ft_strsub((*input)->line, (*input)->cur_pos,
			((*input)->lenght - (*input)->cur_pos))))
		return (NULL);
	ft_strdel(&(*input)->line);
	if (!(ret = ft_strjoin_free(str2, str3, 2)))
		return (NULL);
	return (ret);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'ctrl + v' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_ctrl_v(t_line **input, char ch)
{
	if (ch != KP_CTRL_V)
		return (0);
	if (!g_clipboard)
		return (1);
	else
	{
		if ((*input)->line)
		{
			if (!((*input)->line = input_insert(input, g_clipboard)))
				return (-1);
		}
		else
		{
			if (!((*input)->line = ft_strdup(g_clipboard)))
				return (-1);
		}
		(*input)->lenght += ft_strlen(g_clipboard);
		(*input)->cur_pos += ft_strlen(g_clipboard);
	}
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Alternative for disp_line, which display the selected input as inversed.
**	-------------------------------------------------------------------------- +
*/

static void	disp_select(t_line *input, int start, int len)
{
	int		i;

	i = input->cur_pos;
	while (i-- > 0)
		ft_putstr(ESC_LEFT_ARROW);
	ft_putstr(ESC_CLRSCR);
	ft_putchar('\r');
	sh_prompt();
	i = 0;
	while (*(input->line + i))
	{
		if (i == start)
			ft_putstr(C_INVERSE_ON);
		if (i == len)
			ft_putstr(C_INVERSE_OFF);
		ft_putchar(*(input->line + i++));
	}
	i = input->cur_pos;
	while (i++ < input->lenght)
		ft_putstr(ESC_LEFT_ARROW);
}

/*
**	-------------------------------------------------------------------------- +
**	Removes the selected part from 'input->line' string.
**	-------------------------------------------------------------------------- +
*/

static int	kp_cut(t_line **input, int start)
{
	char	*str1;
	char	*str2;

	if (!(str1 = ft_strsub((*input)->line, 0, start)))
		return (EXIT_FAILURE);
	if (!(str2 = ft_strsub((*input)->line, (*input)->cur_pos,
			(*input)->lenght)))
		return (EXIT_FAILURE);
	ft_strdel(&(*input)->line);
	if (!((*input)->line = ft_strjoin_free(str1, str2, 2)))
		return (EXIT_FAILURE);
	(*input)->lenght -= (*input)->cur_pos - start;
	while ((*input)->cur_pos > start)
	{
		(*input)->cur_pos--;
		ft_putstr(ESC_LEFT_ARROW);
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'ctrl + s' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_ctrl_s(t_line **input, char ch)
{
	int	mem;

	if (ch != KP_CTRL_S || (*input)->cur_pos == (*input)->lenght)
		return (0);
	mem = (*input)->cur_pos;
	while (1)
	{
		if ((ch = ft_getch()) == '\n')
			break ;
		else if (ch == KP_CTRL_S)
		{
			kp_right_arrow(input, CH_RIGHT);
			disp_select(*input, mem, (*input)->cur_pos);
		}
		else if (ch == KP_CTRL_B || ch == KP_CTRL_X)
		{
			ft_strdel(g_clipboard ? &g_clipboard : 0);
			if (!(g_clipboard = ft_strsub((*input)->line,
					mem, (*input)->cur_pos - mem)))
				return (-1);
			if (ch == KP_CTRL_X)
				if (kp_cut(input, mem) == EXIT_FAILURE)
					return (-1);
			break ;
		}
	}
	return (1);
}
