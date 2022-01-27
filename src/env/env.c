#include "../../inc/minishell.h"

void	env_func(t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp != NULL)
	{
		if (tmp->var != NULL)
		{
			ft_putstr_fd(tmp->var, 1);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}
