#include "minishell.h"

void	unset(char *arg, t_env **env_list)
{
	t_env	*check_node;
	t_env	*prev_node;

	check_node = *env_list;
	if (!arg || *env_list == NULL)
		return ;
	while (ft_strncmp(arg, check_node->var, ft_strlen(arg)) != 0)
	{
		prev_node = check_node;
		check_node = check_node->next;
		if (check_node == NULL)
			return ;
	}
	prev_node->next = check_node->next;
	free(check_node->var);
	free(check_node);
}
