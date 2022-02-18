#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
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

typedef struct s_mini
{
    char            *mini_cwd;
    char            *argv;
	struct s_arg	*first;
	struct s_arg	*current;
	int		        fd_history;
}               t_mini;

typedef struct s_arg
{
    char            **args;
    struct s_arg    *next;
}           t_arg;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_dollvar
{
    int     j;
    char    *ret;
    char    *tmp;
    char    *value;
    int     flag;
}           t_dollvar;

// MiniShell - minishell.c
void	init_mini(t_mini *shell, t_env **env);
void	init_env(t_env **env_list, char **env);
void	exit_shell(t_mini *shell);

// MiniShell - prompt_msg.c
char    *sub_path(char *path);
void	prompt_msg(t_mini *shell);

// MiniShell - working_history.c
void	working_history(t_mini *shell);

// Echo - echo.c
void	echo_func(t_mini *shell);

// Env - env.c
void	env_func(t_env **env_list);

// Env - chained_list.c
t_env	*create_node(char *var_array);
t_env	*dup_node(char *name, char *value);
void	add_to_list(t_env **env_list, t_env *new_node);
void	delete_list(t_env *env_list);
t_env	*sort_list_export(t_env **env_list);
t_env	*duplicate_list(t_env **env_list);
int		count_list(t_env **list);
t_env	*search_in_env(char	*var, t_env **env_list);

// Export - export.c
char	**env_duplicate(char **envp);
void	print_export_list(t_env **env_list);
void	add_var_to_list(t_env **env_list, char *args);
void	export_func(t_env **env_list, char *args);


// EXECUTION - execution.c


// Sgnal - signal.c
void	handler(int sig);

// CD - cd.c
int     cd(char *path);

// Parse - parsing.c
void	parsing(t_mini *shell, t_env **env_list);
// NOT REFACTORED
int	is_w_space(char c);
int print_sep_error(char sep);
int	is_sep(char c);
int	print_quote_err(void);
int	count_arr(char **tab);
void	skip_w_space(char *str, int *i);
int	have_a_dollar(char *str, int i);
char *find_env_var(char *str, int *i, t_env **env_list);
void	skip_quote(char *str, int *i);
int	count_sep(char *str);
int	count_space(char *str);
int	*parse_sep(char *str);
int	*parse_space(char *str);
int	count_missing_space(char *str, int *sep);
void	delete_last_spaces(char **str);
char	*pimp_my_string(t_mini *shell, int *sep);
int	count_nb_wrd(int *sep, int *space);
void	fill_array(t_mini *shell, int **sep, int **space, int *i);
void	create_sep_node(t_mini *shell, int *i, int **space);
void	alloc_args_tab(t_mini *shell, int *sep, int *space);
int	detect_quote(char *str);
void	delete_quote(t_mini *shell, int i, int *j);
void	realloc_args(t_mini *shell, t_env **env_list, int j, int i);
void	quote_remover(t_mini *shell, t_env **env_list, int i);
void	quotes_cleaner(t_mini *shell, t_env **env_list);
int	have_a_dollar_out_q(char *str);
int	realloc_string(t_mini *shell, int i, char *s2);
void	dollar_out_quote(t_mini *shell, t_env **env_list);
int	check_quote_err(char *str);
int	str_error(char *str, int ret);
int	check_args_error(char *str);
int	split_arg(t_mini *shell, t_env **env_list);


// Parse - list_parsing.c
void	init_args(t_mini *shell);
void	add_sep_to_lst(t_mini *shell, int *i);
char	*add_sep_to_node(t_mini *shell, int *i);
void	create_n_add_empty_node(t_mini *shell);
void	destroy_arg_lst(t_mini *shell);

// Parse - replace_dollars.c
char    *replace_dollars(char *str, t_env **env_list, int i, int flag);
void    init_dollvar(t_dollvar *data, int i, int flag);
char    *append(t_dollvar *data);
int     get_value_in_str(char *str, int *i, t_dollvar *data, t_env **env_list);
int     find_dollars_str(char *str, int *i, t_dollvar *data, t_env **env_list);

// PWD - pwd.c
void    pwd(void);

//UNSET - unset.c
void	unset(char *arg, t_env **env_list);

#endif
