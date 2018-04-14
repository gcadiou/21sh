/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apedron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 12:03:33 by apedron           #+#    #+#             */
/*   Updated: 2018/04/14 16:48:57 by gcadiou          ###   ########.fr       */
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

/*
**	-------------------------------------------------------------------------- +
**	STRUCTURES, LINKED LISTS
**	-------------------------------------------------------------------------- +
*/

typedef struct	s_hist
{
	char			*line;
	int				current;
	struct s_hist	*next;
}				t_hist;

t_hist			*g_hist;

typedef struct	s_line
{
	char			*line;
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

typedef struct	s_token
{
	char			*content;
	char			*heredoc;
	int				type;
	struct s_token	*next;
}				t_token;

typedef struct	s_ast
{
	t_token			*token;
	struct s_ast	*up;
	struct s_ast	*left;
	struct s_ast	*right;
	int				ret;
}				t_ast;

int				g_status;

typedef struct	s_redir
{
	int				old;
	int				save;
	struct s_redir	*next;
}				t_redir;

typedef struct	s_df
{
	int			in;
	int			out;
	int			err;
}				t_df;

typedef struct	s_pipe
{
	char	***cmds;
	t_token	**tokens;
}				t_pipe;

/*
**	-------------------------------------------------------------------------- +
**	FUNCTIONS
**	-------------------------------------------------------------------------- +
*/

int				ast_build(t_ast **head, t_token *tokens, char **heredocs);

char			**token_into_array(t_token *tokens);
int				ast_pipe(t_ast *ast);
int				read_ast(t_ast *ast);

void			cmd_exec(char **cmd, t_token *token);
int				cmd_exec_s(char **cmd, t_token *token, int *status);
int				cmd_exec_p(char ***cmds, t_token **tokens, int *status);
int				cmd_exec_pipe(t_pipe data, int *status, size_t pos, int fd_in);
int				cmd_exec_p_builtins(char **cmd, t_token *token);

int				cmd_check_perm(char *cmd, char *path, int ret);
int				cmd_get_path(char *cmd, char **path);
void			cmd_err_msg(char *cmd);

int				cmd_redir(t_token *head, int mode);
int				cmd_redir_df_set(t_df *df);
int				cmd_redir_df_get(t_df *df, int val);
void			cmd_redir_df_res(t_df *df);
int				cmd_redir_fds_add(t_redir **head, int fd_old, int fd_save);
void			cmd_redir_fds_rev(t_redir **head);

int				cmd_redir_agre(t_token *prev, t_token *curr, t_redir **fds,
		t_df *df);
int				cmd_redir_input(t_token *prev, t_token *curr, t_redir **fds,
		t_df *df);
int				cmd_redir_output(t_token *prev, t_token *curr, t_redir **fds,
		t_df *df);

int				env_remove(char *name);
int				env_replace(char *name, char *value);
int				env_append(char *name, char *value);
int				env_entry_exists(char *name);
char			*env_get_val(char *name);

int				handle_heredocs(char ***heredocs, char *input);

int				hist_append(t_hist **head, char *input);
void			hist_init(t_hist **head);
void			hist_print(t_hist *head);
t_hist			*hist_getnoc(t_hist **head);
t_hist			*hist_getpoc(t_hist **head);

int				input_catch(char **input, char ***heredocs);
int				input_read(char **input, int mode);
void			input_disp(t_line *head, char ch, int key, int mode);
void			input_clear_line(t_line *head);
void			input_reset_cursor(t_line *head);

int				kp_backspace(t_line **head, char ch, int mode);
int				kp_ctrl_d(t_line **head, char ch, int mode);
int				kp_ctrl_l(t_line **head, char ch, int mode);
int				kp_esc_seq(t_line **head, char ch, int mode);
int				kp_end(t_line **head, char ch);
int				kp_ctrl_e(t_line **head, char ch, int mode);
int				kp_home(t_line **head, char ch);
int				kp_ctrl_a(t_line **head, char ch, int mode);
int				kp_down_arrow(t_line **head, char ch);
int				kp_up_arrow(t_line **head, char ch);
int				kp_left_arrow(t_line **head, char ch);
int				kp_right_arrow(t_line **head, char ch);
int				kp_opt_down_arrow(t_line **head, char ch);
int				kp_opt_up_arrow(t_line **head, char ch);
int				kp_opt_left_arrow(t_line **head, char ch);
int				kp_opt_right_arrow(t_line **head, char ch);
int				kp_select(t_line **head, char ch, int mode);
int				kp_paste(t_line **head, char ch, int mode);

int				env_init(void);
void			free_ast(t_ast **head);
void			free_hist(t_hist **head);
void			free_token(t_token **head);

void			mc_left(t_line *head);
void			mc_right(t_line *head);

int				my_cd(char **args, int *status);
int				my_echo(char **args, int *status);
int				my_env(char **args, int *status);
int				my_env_exec(char **cmd, int *status, char **env);
int				my_env_append(char ***env, char *name, char *value);
int				my_exit(char **args, int *status);
int				my_setenv(char **args, int *status);
int				arg_is_alnum(char *arg, char *name);
int				my_unsetenv(char **args, int *status);

int				eat(t_token**tlist, int token_type);
int				is_command(t_token **tlist);
int				is_command_elem(t_token **tlist);
int				is_word(t_token **tlist);
int				is_redirection(t_token **tlist);
int				is_simple_redirection(t_token **tlist);
int				is_io_redirection(t_token **tlist);
int				is_io_redirection2(t_token **tlist);
int				is_io_redirection3(t_token **tlist);
int				is_close_redirection(t_token **tlist);
int				is_close_redirection2(t_token **tlist);

int				get_window_size(int *rows, int *cols);
int				sh_return(char *message);
void			sh_exit(char *message);
void			sh_prompt(int mode);

void			signal_handler(void);
void			sig_kill(int sig);
void			sig_exe(int sig);
void			sig_int(int sig);

int				tc_putc(int c);

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
int				token_rework(t_token **head);
void			token_del_node(t_token **head, t_token *node);
void			token_del_some(t_token **head, int type);
int				token_merge(t_token **head);
int				token_substitute(t_token **head);
int				token_append(t_tokenizer *data, char ch);
int				token_add(t_token **head, char *content, int type);
int				token_type(char *content, int type);
int				token_is_operator(char *token);
int				token_is_operator_first_char(char fc);
int				tokenizer(char *input, t_token **tlist);

#endif
