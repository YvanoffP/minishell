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
# include "../libft/libft.h"

typedef struct s_mini
{
    char    *mini_cwd;
    char    *argv;
}               t_mini;

// MiniShell - minishell.c
void	init_mini(t_mini *shell);
void	exit_shell(t_mini *shell);

// MiniShell - prompt_msg.c
char    *sub_path(char *path);
void	prompt_msg(t_mini *shell);

// Echo - echo.c
void	echo_func(char *str, int flag);

// Export - export.c
void	export_func(char **envp);

// CD - cd.c
int     cd(char *path);

// PWD - pwd.c
void    pwd(void);

#endif
