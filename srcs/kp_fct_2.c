/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kp_fct_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:39:51 by apedron           #+#    #+#             */
/*   Updated: 2018/03/19 15:04:40 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles 'end' key, and 'ctrl + e' key combination (alias for 'end').
**	-------------------------------------------------------------------------- +
*/

int	kp_end(t_line **head, char ch)
{
	if (ch != CH_END)
		return (0);
	while ((*head)->cur_pos < (int)ft_strlen((*head)->line))
		mc_right(*head);
	return (KEY_END);
}

int	kp_ctrl_e(t_line **head, char ch, int mode)
{
	(void)mode;
	if (ch != KP_CTRL_E)
		return (0);
	return (kp_end(head, CH_END));
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'home' key, and 'ctrl + a' key combination (alias for 'home').
**	-------------------------------------------------------------------------- +
*/

int	kp_home(t_line **head, char ch)
{
	if (ch != CH_HOME)
		return (0);
	while ((*head)->cur_pos > 0)
		mc_left(*head);
	return (KEY_HOME);
}

int	kp_ctrl_a(t_line **head, char ch, int mode)
{
	(void)mode;
	if (ch != KP_CTRL_A)
		return (0);
	return (kp_home(head, CH_HOME));
}
