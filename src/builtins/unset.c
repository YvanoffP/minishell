#include "minishell.h"

void	unset(t_mini *shell, t_env **env_list)
{
	t_env	*check_node;
	t_env	*prev_node;
	int		i;

	i = 1;
	check_node = *env_list;
	if (!shell->current->args[i] || *env_list == NULL)
		return ;
	while (ft_strcmp(shell->current->args[i], check_node->var) != 0 && shell->current->args[i])
	{
		prev_node = check_node;
		check_node = check_node->next;
		if (check_node == NULL)
			return ;
	}
	prev_node->next = check_node->next;
	free(check_node->var);
	free(check_node->value);
	free(check_node);
}
