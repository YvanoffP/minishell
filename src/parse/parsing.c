/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_env_var(char *str, int *i, t_env **env_list)
{
	char	*name;
	int		j;
	t_env	*list;

	*i += 1;
	j = *i;
	list = *env_list;
	while (!is_w_space(str[*i]) && str[*i] && str[*i] != '$'
		&& str[*i] != 34 && str[*i] != 39 && str[*i] != '=')
		*i += 1;
	name = ft_substr(str, j, (*i - j));
	while (ft_strcmp(name, list->var) && list->next != NULL)
		list = list->next;
	if (ft_strcmp(name, list->var))
	{
		free(name);
		return (NULL);
	}
	free(name);
	name = ft_strdup(list->value);
	return (name);
}

int	count_cmd(int *sep)
{
	int	i;

	i = 0;
	while (*sep)
	{
		sep++;
		i++;
	}
	return (i + 1);
}

void	destroy_sep_n_space(int **sep, int **space)
{
	free(*sep);
	free(*space);
}

int	split_arg(t_mini *shell, t_env **env_list)
{
	int	*sep;
	int	*space;
	int	*ptr;

	if (check_quote_err(shell->argv))
		return (0);
	if (check_args_error(shell->argv))
		return (str_error("Args error detected", 0));
	sep = parse_sep(shell->argv);
	if (sep == NULL)
		return (str_error("Sep error detected", 0));
	shell->argv = pimp_my_string(shell, sep);
	free(sep);
	sep = parse_sep(shell->argv);
	space = parse_space(shell->argv);
	shell->cmd_count = count_cmd(sep);
	init_child(shell);
	ptr = sep;
	while (*(ptr++))
		create_n_add_empty_child(shell);
	alloc_childs(shell, sep, space);
	destroy_sep_n_space(&sep, &space);
	dollar_out_quote(shell, env_list);
	quotes_cleaner(shell, env_list);
	return (1);
}

int	parsing(t_mini *shell, t_env **env_list)
{
	if (!split_arg(shell, env_list))
		return (0);
	return (1);
}
