/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kp_fct_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:28:32 by apedron           #+#    #+#             */
/*   Updated: 2018/03/19 15:04:28 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles 'down arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_down_arrow(t_line **head, char ch)
{
	t_hist	*node;

	if (ch != CH_DOWN)
		return (0);
	input_clear_line(*head);
	if (!(node = hist_getnoc(&g_hist)))
	{
		if (!g_hist)
			return (KEY_DOWN_ARROW);
		ft_strdel(&(*head)->line);
		if (!((*head)->line = ft_strdup("")))
			return (-1);
		(*head)->cur_pos = 0;
		hist_init(&g_hist);
	}
	else
	{
		ft_strdel(&(*head)->line);
		if (!((*head)->line = ft_strdup(node->line)))
			return (-1);
		(*head)->cur_pos = ft_strlen((*head)->line);
	}
	return (KEY_DOWN_ARROW);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'up arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_up_arrow(t_line **head, char ch)
{
	t_hist	*node;

	if (ch != CH_UP)
		return (0);
	input_clear_line(*head);
	if (!(node = hist_getpoc(&g_hist)))
		return (KEY_UP_ARROW);
	ft_strdel(&(*head)->line);
	if (!((*head)->line = ft_strdup(node->line)))
		return (-1);
	(*head)->cur_pos = ft_strlen((*head)->line);
	return (KEY_UP_ARROW);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'left arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_left_arrow(t_line **head, char ch)
{
	if (ch != CH_LEFT)
		return (0);
	if ((*head)->cur_pos > 0)
		mc_left(*head);
	return (KEY_LEFT_ARROW);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'right arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_right_arrow(t_line **head, char ch)
{
	if (ch != CH_RIGHT)
		return (0);
	if ((*head)->cur_pos < (int)ft_strlen((*head)->line))
		mc_right(*head);
	return (KEY_RIGHT_ARROW);
}
