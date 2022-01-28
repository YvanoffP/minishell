#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
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

typedef struct s_mini
{
    char    *mini_cwd;
    char    *argv;
}               t_mini;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}			t_env;

// MiniShell - minishell.c
void	init_mini(t_mini *shell, t_env **env);
void	init_env(t_env **env_list, char **env);
void	exit_shell(t_mini *shell);

// MiniShell - prompt_msg.c
char    *sub_path(char *path);
void	prompt_msg(t_mini *shell);

// Echo - echo.c
void	echo_func(char *str, int flag);

// Env - env.c
void	env_func(t_env **env_list);
// Env - chained_list.c
t_env	*create_node(char *var_array);
void	add_to_list(t_env **env_list, t_env *new_node);
void	delete_list(t_env *env_list);
t_env	*sort_list_export(t_env **env_list);
t_env	*duplicate_list(t_env **env_list);
int		count_list(t_env **list);

// Export - export.c
char	**env_duplicate(char **envp);
void	print_export_list(t_env **env_list);
void	add_var_to_list(t_env **env_list, char *args);
void	export_func(t_env **env_list, char *args);

// Sgnal - signal.c
void	handler(int sig);

// CD - cd.c
int     cd(char *path);

// PWD - pwd.c
void    pwd(void);

#endif
