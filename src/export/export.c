#include "../../inc/minishell.h"

static char	**env_duplicate(char **envp)
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

static void	display_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
}

void	export_func(char **envp)
{
	char 	**env_dup;
	char	*tmp;
	int		flag;
	int		i;

	env_dup = env_duplicate(envp);
	flag = 0;
	while (env_dup[flag])
	{
		i = flag + 1;
		while (env_dup[i])
		{
			if (ft_strcmp(env_dup[flag], env_dup[i]) > 0)
			{
				tmp = env_dup[flag];
				env_dup[flag] = env_dup[i];
				env_dup[i] = tmp;
			}
			i++;
		}
		flag++;
	}
	display_tab(env_dup);
	free_array(env_dup);
}
