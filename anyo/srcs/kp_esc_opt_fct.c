/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kp_esc_seq_opt_fct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:29:16 by apedron           #+#    #+#             */
/*   Updated: 2018/01/19 18:51:49 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles 'option + down arrow' key combination.
**	-------------------------------------------------------------------------- +
*/

int	kp_opt_down_arrow(t_line **input, char ch)
{
	int	rows;
	int	cols;
	int	i;

	if (ch != CH_DOWN)
		return (0);
	get_window_size(&rows, &cols);
	if ((*input)->cur_pos < ((*input)->lenght - cols))
	{
		i = 0;
		while (i < cols)
		{
			ft_putstr(ESC_RIGHT_ARROW);
			(*input)->cur_pos++;
			i++;
		}
	}
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'option + up arrow' key combination.
**	-------------------------------------------------------------------------- +
*/

int	kp_opt_up_arrow(t_line **input, char ch)
{
	int	rows;
	int	cols;
	int	i;

	if (ch != CH_UP)
		return (0);
	get_window_size(&rows, &cols);
	if ((*input)->cur_pos >= cols)
	{
		i = 0;
		while (i < cols)
		{
			ft_putstr(ESC_LEFT_ARROW);
			(*input)->cur_pos--;
			i++;
		}
	}
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'option + left arrow' key combination.
**	-------------------------------------------------------------------------- +
*/

int	kp_opt_left_arrow(t_line **input, char ch)
{
	int	i;

	if (ch != CH_LEFT)
		return (0);
	if ((*input)->cur_pos < 1)
		return (1);
	i = (*input)->cur_pos;
	while (i > 0 && (*input)->line[i - 1] == ' ')
	{
		ft_putstr(ESC_LEFT_ARROW);
		(*input)->cur_pos--;
		i--;
	}
	while (i > 0 && (*input)->line[i - 1] != ' ')
	{
		ft_putstr(ESC_LEFT_ARROW);
		(*input)->cur_pos--;
		i--;
	}
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'option + right arrow' key combination.
**	-------------------------------------------------------------------------- +
*/

int	kp_opt_right_arrow(t_line **input, char ch)
{
	int	i;

	if (ch != CH_RIGHT)
		return (0);
	if ((*input)->cur_pos >= (*input)->lenght)
		return (1);
	i = (*input)->cur_pos;
	while (i < (*input)->lenght && (*input)->line[i + 1] != ' ')
	{
		ft_putstr(ESC_RIGHT_ARROW);
		(*input)->cur_pos++;
		i++;
	}
	while (i < (*input)->lenght && (*input)->line[i + 1] == ' ')
	{
		ft_putstr(ESC_RIGHT_ARROW);
		(*input)->cur_pos++;
		i++;
	}
	return (1);
}
