#include "../../inc/minishell.h"

char	**args_to_array(t_command *child)
{
	t_built_args	*tmp;
	char			**arg;
	int				i;

	tmp = child->args;
	i = count_args(tmp) + 1;
	arg = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	arg[i++] = ft_strdup(child->cmd);
	while (tmp != NULL)
	{
		arg[i++] = ft_strdup(tmp->name);
		tmp = tmp->next;
	}
	arg[i] = NULL;
	return (arg);
}

int	backup(int flag)
{
	static int	stdin;
	static int	stdout;
	static int	stderr;

	if (flag)
	{
		stdin = dup(STDIN_FILENO);
		stdout = dup(STDOUT_FILENO);
		stderr = dup(STDERR_FILENO);
	}
	else if (!flag)
	{
		dup2(stdin, 0);
		dup2(stdout, 1);
		dup2(stderr, 2);
	}
	return (1);
}

int	count_args(t_built_args *lst)
{
	t_built_args	*tmp;
	int				i;

	tmp = lst;
	i = 0;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
		i++;

	}
	return (i);
}

int	print_error(char *str, char *msg, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	if (str != NULL)
		ft_putstr_fd(str, 2);
	ft_putendl_fd(msg, 2);
	return (ret);
}

char	**lst_to_array(t_env **env_list)
{
	char	**ret;
	t_env	*tmp;
	int		i;

	tmp = *env_list;
	i = count_list(env_list);
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (tmp != NULL)
	{
		ret[i] = ft_strjoin(tmp->var, tmp->value);
		i++;
		tmp = tmp->next;
	}
	ret[i] = NULL;
	return (ret);
}
