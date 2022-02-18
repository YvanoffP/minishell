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
int		is_in_lst(char	*var, t_env **env_list);
t_env	*get_in_lst(char *var, t_env **env_list);
void	replace_in_lst(t_env *new_node, t_env **env_list);

// Export - export.c
char	**env_duplicate(char **envp);
void	print_export_list(t_env **env_list);
void	add_var_to_list(t_env **env_list, char *args);
int		export_func(t_env **env_list, t_mini *shell);
int		check_wrong_char(char *str);
int		check_args(t_mini *shell, int i);
int		is_num(char c);
int		check_only_num(char *str);


// EXECUTION - execution.c


// Sgnal - signal.c
void	handler(int sig);

// CD - cd.c
int     cd(char *path);

// Parse - parsing.c
void	parsing(t_mini *shell, t_env **env_list);
int		str_error(char *str, int ret);
int		is_sep(char c);

// Parse - list_parsing.c
void	init_args(t_mini *shell);
void	add_sep_to_lst(t_mini *shell, int *i);
char	*add_sep_to_node(t_mini *shell, int *i);
void	create_n_add_empty_node(t_mini *shell);
void	destroy_arg_lst(t_mini *shell);

// PWD - pwd.c
void    pwd(void);

//UNSET - unset.c
void	unset(char *arg, t_env **env_list);

#endif
