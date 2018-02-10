/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:31:51 by apedron           #+#    #+#             */
/*   Updated: 2018/02/08 15:10:21 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Refreshes the command line (clear + print) on each new byte added to the
**	command. It permits real-time display of what is typed.
**	- mode == 0	->	clear the line
**	- mode > 0	->	print input content
**	- mode > 1	->	print quote-style-prompt instead of classic shell one
**	-------------------------------------------------------------------------- +
*/

void		disp_line(t_line *input, int mode)
{
	int	i;

	i = input->cur_pos;
	while (i-- > 0)
		ft_putstr(ESC_LEFT_ARROW);
	ft_putstr(ESC_CLRSCR);
	if (mode > 0)
	{
		ft_putchar('\r');
		if (mode > 1)
			sh_prompt_q();
		else
			sh_prompt();
		ft_putstr(input->line);
		i = input->cur_pos;
		while (i++ < input->lenght)
			ft_putstr(ESC_LEFT_ARROW);
	}
}

/*
**	-------------------------------------------------------------------------- +
**	On status 1, allocates & initializes the linked list.
**	On status 0, releases the memory allocated by the linked list.
**	-------------------------------------------------------------------------- +
*/

static int	t_line_tools(t_line **head, int status)
{
	if (status == 1)
	{
		if (!(*head = ft_memalloc(sizeof(t_line))))
			return (EXIT_FAILURE);
		(*head)->lenght = 0;
		(*head)->cur_pos = 0;
	}
	if (status == 0)
	{
		ft_strdel(&(*head)->line);
		free(*head);
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Inserts the given character in the string at cursor position.
**	-------------------------------------------------------------------------- +
*/

static int	isrt_char(t_line *input, char ch)
{
	char	*str1;
	char	*str2;

	if (ch == '\n')
		input->cur_pos = input->lenght;
	if (!input->line)
		if (!(input->line = ft_strnew(0)))
			return (EXIT_FAILURE);
	if (!(str1 = ft_strsub(input->line, 0, (input->cur_pos + 1))))
		return (EXIT_FAILURE);
	*(str1 + input->cur_pos) = ch;
	if (!(str2 = ft_strsub(input->line, input->cur_pos,
			(input->lenght - input->cur_pos))))
		return (EXIT_FAILURE);
	input->lenght++;
	ft_strdel(&input->line);
	if (!(input->line = ft_strjoin_free(str1, str2, 2)))
		return (EXIT_FAILURE);
	input->cur_pos++;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Has two behaviors. If the user inputs printable characters, it simply
**	returns it. Else, the function returns 0 (null character), and the program
**	behave as it should if the input is a special character/escape sequence/etc.
**	It can also return -1 on error.
**	-------------------------------------------------------------------------- +
*/

static char	process_keypress(t_line **input)
{
	static int	(*kp_fct[])(t_line **, char) = {
	&kp_backspace,
	&kp_ctrl_c,
	&kp_ctrl_d,
	&kp_ctrl_l,
	&kp_ctrl_s,
	&kp_ctrl_v,
	&kp_esc_seq,
	NULL};
	char		ch;
	int			i;

	i = 0;
	ch = ft_getch();
	if (ch == '\n' || (ch >= 32 && ch <= 126))
		return (ch);
	while (kp_fct[i] && kp_fct[i](input, ch) == 0)
		i++;
	return (0);
}

/*
**	-------------------------------------------------------------------------- +
**	Reads byte after byte what the user types, creates a string from it
**	(concatenates each character), and stops when the input is a newline (`\n').
**	It also does stuff on special inputs (backspace, arrow keys, etc).
**	('int mode' is an indicator for disp_line(), see its description)
**	-------------------------------------------------------------------------- +
*/

int			input_read(char **line, int mode)
{
	t_line	*input;
	char	ch;

	if (raw_term_mode() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (t_line_tools(&input, 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (1)
	{
		if ((ch = process_keypress(&input)) == -1)
			return (EXIT_FAILURE);
		else if (ch > 0)
		{
			if (isrt_char(input, ch) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		disp_line(input, mode);
		if (ch == '\n')
			break ;
	}
	if (!(*line = ft_strndup(input->line, ft_strlen(input->line) - 1)))
		return (EXIT_FAILURE);
	if (hist_append(&g_hist, *line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	hist_reset(&g_hist);
	if (def_term_mode(-1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (t_line_tools(&input, 0));
}
