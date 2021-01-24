/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 17:32:36 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 21:23:25 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../mylib/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <termcap.h>

typedef struct dirent	t_dirent;
typedef struct termios	t_termios;
typedef struct stat		t_stat;

typedef struct		s_termcap_cmd
{
	char			*cl;
	char			*reset;
	char			*nd;
	char			*le;
	char			*ed;
	char			*dm;
	char			*ei;
	char			*im;
	char			*dc;
}					t_termcap;

typedef struct		s_env
{
	char			*var;
	char			*value;
	int				exp;
	struct s_env	*next;
}					t_env;

typedef struct		s_hist
{
	char			*line;
	struct s_hist	*previous;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_parse
{
	int				quo;
	int				dquo;
	int				assignment;
	int				unassignable;
}					t_parse;

typedef struct		s_all
{
	int				pipe[2];
	int				depth;
	int				index;
	int				status;
	int				free_command;
	int				assignable;
	char			**full_command;
	char			**path_auto;
	char			**env_array;
	char			**args_array;
	char			copy[200];
	t_env			*env_list;
	t_list			*args_beg;
	t_list			*args_rd;
	t_list			*args_pipe;
	t_list			*cmds;
	t_list			*args;
	t_hist			**history;
	t_hist			*current;
	t_parse			*parse;
	t_termcap		*term;
	t_termios		*new_termios;
	t_termios		*old_term;
}					t_all;

/*
**				DEBUG
*/

void				dump_cmds(t_all *all);

/*
**				HISTORY
*/

t_hist				*ft_new_hist(void *content);
void				ft_clear_history(t_hist **lst, void (*del)(void*));
void				ft_add_hist(t_hist **alst, t_hist *new);
void				previous_history(t_all *all, char **res);
void				next_history(t_all *all, char **res);
void				save_history(t_hist **history);
void				load_history(t_hist **history);
void				prepare_history(t_all *all, char **res);
void				history_choice(t_all *all, char **res, int buffer);

/*
**				TERMCAPS
*/

int					init_termcap(t_termcap *tc_cmd, t_all *all, int ret);
int					gnl(int fd, char **line, int buffer_size, t_all *all);
int					retour_termcap(t_all *all, char **buffer, char **res);
int					delete(t_all *all, char **buffer, char **res, int len);
char				**set_line(t_all *all, char **res, char *buffer, int *ret);
void				previous_word(t_all *all, char **res, int len);
void				next_word(t_all *all, char **res, int len);
void				s_e_line(t_all *all, int s_e, int len);
void				ft_copy(t_all *all, char **res);
void				ft_paste(t_all *all, char **res, int len);
void				prompt(t_all *all, char **buffer, char **res, int len);
void				print_name(void);
void				handler(int signo);
void				actual_path(int status);

/*
**				CMD
*/

int					ft_pwd(t_all *all);
int					ft_chdir(t_all *all);
int					ft_echo(t_all *all);
int					ft_exec(t_all *all);
int					skip_args(t_list *args);
int					ft_redirection(t_all *all, char *buffer);
void				next_args(t_list **args);
void				format_echo_output(t_all *all, char **buffer, int *boolean);

/*
**				PARSING
*/

int					parse_command(char *command, t_all *all);
int					parse_args_to_lists(char *command, t_all *all, int i,
					int script);
int					split_command(char *complete_command, t_all *all);
int					is_redir_oplog(char *cmd, int i);
int					check_if_redir_oplog(char *cmd, t_list **args, int *i,
					t_all *all);
int					parse_loop(char *cmd, char **trim, int *i, t_all *all);
int					check_if_parenthesis(char *cmd, t_list **args, int *i);
int					find_command(t_all *all);
int					check_syntax(char *s, t_all *all);
int					return_status(t_all *all, int errcode);
int					end_line(char *s);
int					limite(char *s, int i, int cpt);
int					trim_cmd(char *cmd, char **trim, int *i, t_all *all);
int					to_dollar(char *cmd, char **trim, int *i, t_all *all);
int					to_quote(char **trim, int *i, t_all *all);
int					to_dquote(char **trim, int *i, t_all *all);
int					to_bslash(char *cmd, char **trim, int *i, t_all *all);
int					to_equal(char *cmd, char **trim, int *i, t_all *all);
int					read_quotes(char q, int i, char **trim, t_all *all);
int					match_n_match(char *s, char *type);
void				wildcards(t_list **args);
void				check_cmd(t_list *args);

/*
**				ENV
*/

int					env_len(char **env);
int					env_lstlen(t_env *lst);
int					print_env(t_env *lst);
int					print_env_array(char **env);
int					get_env(t_all *all, char **environ);
int					add_env(t_env **env_list, char *varval, int exp, int i_eq);
void				env_lstaddb(t_env **alst, char *var, char *value, int exp);
int					ft_env(t_all *all);
int					ft_setenv(t_all *all);
int					is_valid_assignment(t_list *args);
int					export_env(t_env **env_list, char *arg);
int					ft_export(t_all *all);
int					ft_unset(t_all *all);
int					unset_env(t_env **env_list, char *arg);
int					export_no_arg(t_all *all);
int					arg_list2array(t_all *all);
int					sort_env_array(t_all *all);
int					env_list2array(t_all *all);
char				*expand_env_var(char *s, t_all *all);

/*
**				AUTOCOMPLETION
*/

char				**save_path(t_env *env_list);
void				autocompletion(t_all *all, char **res);
void				search_cmd(t_all *all, char *res, int len, char **line);

/*
**				PIPE / REDIRECTION
*/

int					check_prd_syntax(t_all *all);
int					len_to_pipe(t_list *lst);
int					parse_pipe_rd(t_all *all);
int					pipe_stdout(t_all *all);
int					setup_pipes_rd(t_all *all);
int					redirect_io(t_all *all, t_list *prd);
int					redir_cleanup(t_all *all);
int					redir_stdin(t_all *all);
int					redir_stdout(t_all *all, char *op);
void				redir_heredoc_child(char *heredoc,
					int stdin_backup, t_all *all);
int					redir_heredoc(t_all *all);
int					is_redirect(t_list *arg);
int					which_prd(t_list *arg);
int					read_prd(t_all *all);
int					complete_read(t_list *lst, t_all *all);
int					parse_pipe(t_all *all);
int					parse_rd(t_all *all);
char				*expand_str(char *str, char *exp, int len_var,
					t_all *all);
int					read_heredoc(char *eofsig, char **heredoc, int ret,
					t_all *all);

/*
**				EVAL
*/

int					check_parenthesis(char *cmd);
int					parse_logic(t_list *args, t_all *all);
int					run_subshell(t_list *args, t_all *all);
int					check_logic(t_all *all);
void				match_parenthesis(char *str, int *i);

/*
**				EXIT
*/

void				ft_exit(t_all *all);
void				exit_err(void);
void				ft_error();
int					free_cmd_args(t_all *all);
int					return_error(t_all *all, char *token, int errcode);
int					print_n_set_error(t_all *all, char *token, char *str,
																int errcode);

#endif
