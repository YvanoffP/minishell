#include "../../inc/minishell.h"

char	**env_duplicate(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	copy[i] = 0;
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	return (copy);
}

void	print_export_list(t_env **env_list)
{
	t_env	*tmp;
	t_env	*sort_list;

	sort_list = sort_list_export(env_list);
	tmp = sort_list;
	while (tmp != NULL)
	{
		if (tmp->var != NULL)
			ft_putstr_fd(tmp->var, 1);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	delete_list(sort_list);
}

void	add_var_to_list(t_env **env_list, char *args)
{
	t_env	*new_node;

	new_node = create_node(args);
	add_to_list(env_list, new_node);
}

void	export_func(t_env **env_list, char *args)
{
	if (!args)
		print_export_list(env_list);
	if (args)
		add_var_to_list(env_list, args);
}
