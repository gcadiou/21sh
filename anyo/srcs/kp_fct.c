/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kp_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:31:46 by apedron           #+#    #+#             */
/*   Updated: 2018/02/09 18:31:58 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles 'backspace' key.
**	-------------------------------------------------------------------------- +
*/

int			kp_backspace(t_line **input, char ch)
{
	int	index;

	if (ch != KP_BACKSPACE)
		return (0);
	if ((*input)->lenght < 1 || (*input)->cur_pos < 1)
		return (1);
	index = (*input)->cur_pos - 1;
	ft_memmove(&(*input)->line[index], &(*input)->line[index + 1],
		ft_strlen((*input)->line) - index);
	ft_putstr(ESC_BACKSPACE);
	(*input)->lenght--;
	(*input)->cur_pos--;
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'ctrl + c' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_ctrl_c(t_line **input, char ch)
{
	if (ch != KP_CTRL_C)
		return (0);
	disp_line(*input, 1);
	ft_putchar('\n');
	sh_prompt();
	signal(SIGINT, sig_int);
	ft_strdel(&(*input)->line);
	if (!((*input)->line = ft_strdup("")))
		return (-1);
	(*input)->lenght = 0;
	(*input)->cur_pos = 0;
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'ctrl + d' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_ctrl_d(t_line **input, char ch)
{
	if (ch != KP_CTRL_D)
		return (0);
	if ((*input)->cur_pos == 0 && (*input)->lenght == 0)
	{
		ft_putendl("exit");
		if (def_term_mode(-1) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else if ((*input)->cur_pos < (*input)->lenght)
	{
		(*input)->cur_pos++;
		kp_backspace(input, KP_BACKSPACE);
	}
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'ctrl + l' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_ctrl_l(t_line **input, char ch)
{
	(void)input;
	if (ch != KP_CTRL_L)
		return (0);
	ft_putstr("\033[2J");
	ft_putstr("\033[1;1H");
	sh_prompt();
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles escape sequences key combination containing 'option' key.
**	-------------------------------------------------------------------------- +
*/

static int	kp_esc_seq_opt(t_line **input, char ch)
{
	static int	(*kp_fct[])(t_line **, char) = {
	&kp_opt_down_arrow,
	&kp_opt_left_arrow,
	&kp_opt_right_arrow,
	&kp_opt_up_arrow,
	NULL};
	int			i;

	if (ch != KP_ESC)
		return (0);
	i = 0;
	ch = ft_getch();
	ch = ft_getch();
	while (kp_fct[i] && kp_fct[i](input, ch) == 0)
		i++;
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles escape sequences keys combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_esc_seq(t_line **input, char ch)
{
	static int	(*kp_fct[])(t_line **, char) = {
	&kp_down_arrow,
	&kp_end,
	&kp_home,
	&kp_left_arrow,
	&kp_right_arrow,
	&kp_up_arrow,
	NULL};
	int			i;

	if (ch != KP_ESC)
		return (0);
	i = 0;
	ch = ft_getch();
	if (ch == CH_SQUARE_BRACKET)
	{
		ch = ft_getch();
		while (kp_fct[i] && kp_fct[i](input, ch) == 0)
			i++;
		return (1);
	}
	else
		return (kp_esc_seq_opt(input, ch));
}
