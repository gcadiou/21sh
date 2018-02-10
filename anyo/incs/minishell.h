/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 12:03:33 by apedron           #+#    #+#             */
/*   Updated: 2018/02/09 18:59:36 by apedron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
**	-------------------------------------------------------------------------- +
**	INCLUDES
**	-------------------------------------------------------------------------- +
*/

# include "./macros.h"
# include "../libft/libft.h"
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <dirent.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <term.h>
# include <errno.h>

/*
**	-------------------------------------------------------------------------- +
**	STRUCTURES, LINKED LISTS
**	-------------------------------------------------------------------------- +
*/

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_cmd
{
	char			**command;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_hist
{
	char			*line;
	int				status;
	struct s_hist	*next;
}				t_hist;

typedef struct	s_token
{
	char			*token;
	char			*value;
	struct s_token	*next;
}				t_token;

typedef struct	s_line
{
	char			*line;
	int				lenght;
	int				cur_pos;
}				t_line;

typedef struct	s_tokenizer
{
	char			*token;
	int				sq;
	int				dq;
	int				bs;
	int				op;
}				t_tokenizer;

/*
**	-------------------------------------------------------------------------- +
**	GLOBAL VARIABLES
**	-------------------------------------------------------------------------- +
*/

t_hist			*g_hist;

/*
**	-------------------------------------------------------------------------- +
**	FUNCTIONS
**	-------------------------------------------------------------------------- +
*/

int				cmd_execute(t_env **env, char **command);

int				cmd_init(t_cmd **cmd, t_env **env, char *line);

int				words_last_c(const char *raw_input, int index);
int				words_first_c(const char *raw_input, int index);
int				words_count(const char *raw_input);

char			**cmd_split(char const *str);

void			cmd_reverse(t_cmd **head);
void			cmd_free(t_cmd **head);
char			**cmd_replace_dots(char **command);

int				env_init(t_env **head);

int				env_remove(t_env **head, char *name);
int				env_replace(t_env **head, char *name, char *value);
int				env_append(t_env **head, char *name, char *value);
int				env_entry_exists(t_env **head, char *name);
char			*env_get_val(t_env **head, char *name);

int				env_len(t_env **head);
void			env_reverse(t_env **head);
void			env_print(t_env *head);
void			env_free(t_env **head);
char			**env_as_array(t_env **head);

int				ft_isspace(int c);
int				ft_strisblank(char *str);

int				get_window_size(int *rows, int *cols);

int				hist_append(t_hist **head, char *input);
t_hist			*hist_getnoc(t_hist **head);
t_hist			*hist_getpoc(t_hist **head);
void			hist_reset(t_hist **head);
void			hist_output(t_hist *head);

int				is_input_empty(const char *input);
int				is_command_empty(char **command);
int				check_quotes(const char *input);
int				input_get(char **input);

int				input_read(char **line, int mode);
void			disp_line(t_line *input, int mode);

int				kp_ctrl_s(t_line **input, char ch);
int				kp_ctrl_v(t_line **input, char ch);

int				kp_opt_up_arrow(t_line **input, char ch);
int				kp_opt_left_arrow(t_line **input, char ch);
int				kp_opt_right_arrow(t_line **input, char ch);
int				kp_opt_down_arrow(t_line **input, char ch);

int				kp_down_arrow(t_line **input, char ch);
int				kp_end(t_line **input, char ch);
int				kp_home(t_line **input, char ch);
int				kp_left_arrow(t_line **input, char ch);
int				kp_right_arrow(t_line **input, char ch);
int				kp_up_arrow(t_line **input, char ch);

int				kp_backspace(t_line **input, char ch);
int				kp_ctrl_c(t_line **input, char ch);
int				kp_ctrl_d(t_line **input, char ch);
int				kp_ctrl_l(t_line **input, char ch);
int				kp_esc_seq(t_line **input, char ch);

int				my_cd(t_env **env, char **command);
int				my_echo(t_env **env, char **command);
int				my_env(t_env **env, char **command);
int				my_exit(t_env **env, char **command);
int				my_setenv(t_env **env, char **command);
int				my_unsetenv(t_env **env, char **command);

int				sh_return(char *message);
void			sh_exit(char *message);
void			sh_prompt(void);
void			sh_prompt_q(void);

void			signal_handler(int mode);
void			sig_int(int sig);
void			sig_exe(int sig);
void			sig_tstp(int sig);

int				def_term_mode(int mode);
int				raw_term_mode(void);

int				token_process_1(t_token **head, t_tokenizer *data, char ch);
int				token_process_2(t_token **head, t_tokenizer *data, char ch);
int				token_process_3(t_token **head, t_tokenizer *data, char ch);
int				token_process_4(t_token **head, t_tokenizer *data, char ch);
int				token_process_5(t_token **head, t_tokenizer *data, char ch);
int				token_process_6(t_token **head, t_tokenizer *data, char ch);
int				token_process_7(t_token **head, t_tokenizer *data, char ch);
int				token_process_8(t_token **head, t_tokenizer *data, char ch);
int				token_process_9(t_token **head, t_tokenizer *data, char ch);
int				token_process_10(t_token **head, t_tokenizer *data, char ch);

int				tokenizer(char *input);
int				token_append(t_tokenizer *data, char ch);
int				token_add(t_token **head, char *token, char *value);
int				token_is_operator(char *token);
int				token_is_operator_first_char(char fc);

#endif
