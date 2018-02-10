/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kp_esc_seq_fct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:28:32 by apedron           #+#    #+#             */
/*   Updated: 2018/01/30 15:57:11 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles 'down arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_down_arrow(t_line **input, char ch)
{
	t_hist	*node;

	if (ch != CH_DOWN)
		return (0);
	disp_line(*input, 0);
	if (!(node = hist_getnoc(&g_hist)))
	{
		if (!g_hist)
			return (1);
		ft_strdel(&(*input)->line);
		if (!((*input)->line = ft_strdup("")))
			return (-1);
		(*input)->lenght = 0;
		(*input)->cur_pos = 0;
	}
	else
	{
		ft_strdel(&(*input)->line);
		if (!((*input)->line = ft_strdup(node->line)))
			return (-1);
		(*input)->lenght = ft_strlen((*input)->line);
		(*input)->cur_pos = ft_strlen((*input)->line);
	}
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'up arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_up_arrow(t_line **input, char ch)
{
	t_hist	*node;

	if (ch != CH_UP)
		return (0);
	disp_line(*input, 0);
	if (!(node = hist_getpoc(&g_hist)))
		return (1);
	ft_strdel(&(*input)->line);
	if (!((*input)->line = ft_strdup(node->line)))
		return (-1);
	(*input)->lenght = ft_strlen((*input)->line);
	(*input)->cur_pos = ft_strlen((*input)->line);
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'left arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_left_arrow(t_line **input, char ch)
{
	if (ch != CH_LEFT)
		return (0);
	if ((*input)->cur_pos < 1)
		return (1);
	ft_putstr(ESC_LEFT_ARROW);
	(*input)->cur_pos--;
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'right arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_right_arrow(t_line **input, char ch)
{
	if (ch != CH_RIGHT)
		return (0);
	if ((*input)->cur_pos >= (*input)->lenght)
		return (1);
	ft_putstr(ESC_RIGHT_ARROW);
	(*input)->cur_pos++;
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'end' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_end(t_line **input, char ch)
{
	if (ch != CH_END)
		return (0);
	while ((*input)->cur_pos < (*input)->lenght)
	{
		ft_putstr(ESC_RIGHT_ARROW);
		(*input)->cur_pos++;
	}
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'home' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_home(t_line **input, char ch)
{
	if (ch != CH_HOME)
		return (0);
	while ((*input)->cur_pos > 0)
	{
		ft_putstr(ESC_LEFT_ARROW);
		(*input)->cur_pos--;
	}
	return (1);
}
