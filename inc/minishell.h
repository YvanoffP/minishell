/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:52:16 by tpauvret          #+#    #+#             */
/*   Updated: 2022/03/07 18:16:28 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <dirent.h>
# include "../src/libft/libft.h"

# define CD "cd"
# define ECHO_CMD "echo"
# define ENV "env"
# define EXPORT "export"
# define EXIT "exit"
# define PWD "pwd"
# define UNSET "unset"
# define YES 1
# define NO 0
# define GREEN "\e[1;32m"
# define RESET "\e[0m"

int	g_infork;

typedef struct s_mini
{
	int					cmd_count;
	struct s_command	*child;
	struct s_process	*exec;
	char				*mini_cwd;
	char				*argv;
	int					fd_history;
	int					status;
}			t_mini;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_dollvar
{
	int		j;
	char	*ret;
	char	*tmp;
	char	*value;
	int		flag;
	int		status;
}			t_dollvar;

/////////PARSING REDIRECTION/////////////////

typedef struct s_alloc
{
	int					*ptr_sep;
	int					*ptr_space;
	int					i;
	int					k;
	int					*dollar_index;
	struct s_command	*child;
	struct s_redir		*tmp;
	struct s_built_args	*temp;
	char				*ret;
	char				quote;
}			t_alloc;

typedef enum e_type{
	GREAT,
	DB_GREAT,
	LESS,
	DB_LESS,
}			t_type;

typedef struct s_redir
{
	char			*file_name;
	t_type			type;
	struct s_redir	*next;
}				t_redir;

typedef struct s_built_args
{
	char				*name;
	struct s_built_args	*next;
}				t_built_args;

typedef struct s_command
{
	char				*cmd;
	t_built_args		*args;
	t_redir				*redirection;
	struct s_command	*next;
}				t_command;

typedef struct s_process
{
	int	*fd;
	int	my_fd[2];
	int	*pid;
	int	cmd_count;
	int	ret;
}			t_process;

//////////////////////////////////////////////

//FILSDEPUTE
void			rl_replace_line(const char *str, int i);

// MiniShell - minishell.c
void			init_mini(t_mini *shell, t_env **env);
void			init_env(t_env **env_list, char **env);
void			exit_shell(t_mini *shell);

// MiniShell - prompt_msg.c
void			prompt_msg(t_mini *shell);

// MiniShell - working_history.c
void			working_history(t_mini *shell);

// Builtins - echo.c
void			echo_func(t_built_args *args);

// Builtins - env.c
void			env_func(t_env **env_list);

// Builtins - chained_list.c
void			replace_in_lst(t_env *new_node, t_env **env_list);
t_env			*get_in_lst(char *var, t_env **env_list);
int				is_in_lst(char	*var, t_env **env_list);
t_env			*sort_list_export(t_env **env_list);
void			delete_list(t_env *env_list);

// Builtins - chained_list_2.c
void			add_to_list(t_env **env_list, t_env *new_node);
t_env			*dup_node(char *name, char *value);
t_env			*duplicate_list(t_env **env_list);
t_env			*create_node(char *var_array);
int				count_list(t_env **list);

// Builtins - chained_list_3.c
void			free_node(t_env *new_node, t_env *tmp, char *str);

// Builtins - swap_nodes.c
void			swap_nodes(t_env *tmp);

// Builtins - export.c
int				export_func(t_env **env_list, t_built_args *args);
int				check_only_num(char *str);
int				check_plus(char *str);
int				check_args(char *name);
int				is_num(char c);

// Builtins - export_2.c
int				add_var_to_list(t_env **env_list, char *args);
void			print_export_list(t_env **env_list);
char			**env_duplicate(char **envp);
int				check_wrong_char(char *str);

// EXECUTION - execution.c
char			*join_path_to_arg(char *path, char *arg);
int				exec_program(t_command *child, t_env **env_list);
int				is_builtins(t_env **env_list, t_command *child);
int				execution(t_env **env_list, t_mini *shell);

// EXECUTION - redirection.c
int				redirection(t_redir *redirection, t_process *proc);
int				db_great_than(int *fd, t_redir *redirection);
int				great_than(int *fd, t_redir *redirection);
int				less_than(int *fd, t_redir *redirection);

// EXCUTION - exec_tools.c
int				print_error(char *str, char *msg, int ret);
char			**args_to_array(t_command *child);
char			**lst_to_array(t_env **env_list);
int				count_args(t_built_args *lst);
int				backup(int flag);

// EXECUTION - file_func.c
void			exec_file(t_command *child, t_env **env_list,
					char *path, int *status);
int				check_file(t_env **env_list, t_command *child);
int				check_path(t_env **env_list, t_command *child);
int				find_file(t_env **env_list, t_command *child);
int				file_error(t_redir *redirection);

// EXECUTION - pipe.c
int				pipe_my_ride(t_mini *shell, t_process *proc, t_env **env_list);
int				close_fd(t_mini *shell, t_process *proc);
int				create_fd_pipe(t_mini *shell, t_process *proc);
int				pipe_fork(t_command	*child, t_env **env_list,
					t_process *proc, int *cmd);

//EXECUTION - heredoc.c
void			exec_db_less(char *stop, int *heredoc_fd);
int				redir_heredocs(t_redir *redir, int *fd, bool last);
int				count_db_less(t_redir *redir);
int				exec_heredocs(t_redir *redir, t_process *proc);
void			process_heredocs(t_mini *shell, t_process *proc);

//EXECUTION - heredocs_utils.c
void			newline(int signal);
void			stop_heredoc(int signal);

// Signal - signal.c
void			run_signals(int sig);
void			restore_prompt(int sig);
void			ctrl_c(int sig);
void			back_slash(int sig);

// Builtins - cd.c
int				cd(t_built_args *args);

// Parse - parsing.c
char			*find_env_var(char *str, int *i, t_env **env_list);
int				count_cmd(int *sep);
int				split_arg(t_mini *shell, t_env **env_list);
int				parsing(t_mini *shell, t_env **env_list);
void			destroy_sep_n_space(int **sep, int **space);

// Parse - alloc_childs.c
void			alloc_childs(t_mini *shell, int *sep, int *space);

// Parse - quote_treatment.c
void			quotes_cleaner(t_mini *shell);
char			*quote_remover(char *str);
char			*delete_quote(char *str, int *j);
char			*realloc_string(char *str, char *s2);

// Parse - arg_redir_nodes.c
t_built_args	*create_args_node(t_mini *shell, int **ptr_space, int *i);
void			add_args_to_child(t_command *child, t_built_args *new);
t_redir			*create_redir_node(t_mini *shell, int **ptr_space, int *i);
void			add_redir_to_child(t_command *child, t_redir *new);

// Parse - dollar_out_quote.c
void			dollar_out_quote(t_mini *shell, t_env **env_list);

// Parse - sep_n_space.c
int				detect_sep(char *str, int *start);
int				*parse_space(char *str);
int				count_space(char *str);
int				*parse_sep(char *str);
int				count_pipe(char *str);

// Parse - error_parse.c
int				str_error(char *str, int ret);
int				check_args_error(char *str);
int				check_quote_err(char *str);

// Parse - pimp_my_string.c
char			*pimp_my_string(t_mini *shell, int *sep);
void			delete_last_spaces(char **str);
int				spaces_to_del(char *str);
void			delete_mid_spaces(char **ret, t_alloc var);

// Parse - pimp_my_string.c
int				count_missing_space(char *str, int *sep);
void			work_nb_n_len(int *nb_space, int *len);
char			*check_around_n_cpy(t_mini *shell, int *ptr, int i, int j);

// Parse - list_parsing.c
void			create_n_add_empty_child(t_mini *shell);
void			init_child(t_mini *shell);

// Parse - parse_tools.c
int				print_sep_error(char sep);
int				print_quote_err(void);
int				count_arr(char **tab);
int				is_w_space(char c);
int				is_sep(char c);

// Parse - parse_tools_2.c
int				check_dollar_validity(char *str, int i);
int				have_a_dollar(char *str, int i);
int				detect_quote(char *str);
void			fill_ret(int **ret);

// Parse - parse_tools_3.c
int				*have_a_dollar_out_q(char *str, int i);
void			skip_w_space(char *str, int *i);
void			skip_quote(char *str, int *i);
void			need_spaces(t_mini *shell, t_env **env_list);
void			check_tild(t_mini *shell);

// Parse - replace_dollars.c
int				get_value_in_str(char *str, int *i,
					t_dollvar *data, t_env **env_list);
int				find_dollars_str(char *str, int *i,
					t_dollvar *data, t_env **env_list);
char			*replace_dollars(char *str, t_env **env_list,
					int *i, t_mini *shell);
void			init_dollvar(t_dollvar *data, int i, t_mini *shell);

// Parse - append.c
char			*append(t_dollvar *data);
char			*append_next(t_dollvar *data);

// Parse - replace_dollars_ext.c
void			replace_dollars_ext(t_dollvar *data, char *str, int *i);

// Builtins - pwd.c
void			pwd(void);

// Builtins - unset.c
void			unset(t_built_args *args, t_env **env_list);

// Builtins - exit.c
void			check_digit(char *arg);
int				check_exit(char *arg);
int				exit_func(t_built_args *args);

#endif
