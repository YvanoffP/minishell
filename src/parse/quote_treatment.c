/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_treatment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*delete_quote(char *str, int *j)
{
	t_alloc	index;

	index.i = 0;
	index.k = 0;
	index.ret = malloc(sizeof(char) * (ft_strlen(str) - 2) + 1);
	if (!index.ret)
		return (NULL);
	while (str[index.k])
	{
		if (index.k == *j)
			index.k++;
		if (str[index.k] != str[*j] || index.k < *j)
			index.ret[index.i++] = str[index.k++];
		if (str[index.k] == str[*j] && index.k > *j)
		{
			*j = index.k++ - 2;
			break ;
		}
	}
	while (str[index.k])
		index.ret[index.i++] = str[index.k++];
	index.ret[index.i] = '\0';
	free(str);
	return (index.ret);
}

char	*quote_remover(char *str)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (str[j] == 34)
		{
			str = delete_quote(str, &j);
			if (str == NULL)
				return (str);
		}
		else if (str[j] == 39)
			str = delete_quote(str, &j);
		j++;
	}
	return (str);
}

void	quotes_cleaner(t_mini *shell)
{
	t_command		*child;
	t_built_args	*tmp;
	t_redir			*t;

	child = shell->child;
	while (child)
	{
		tmp = child->args;
		t = child->redirection;
		if (detect_quote(child->cmd))
			child->cmd = quote_remover(child->cmd);
		while (tmp)
		{
			if (detect_quote(tmp->name))
				tmp->name = quote_remover(tmp->name);
			tmp = tmp->next;
		}
		while (t)
		{
			if (detect_quote(t->file_name))
				t->file_name = quote_remover(t->file_name);
			t = t->next;
		}
		child = child->next;
	}
}

char	*realloc_string(char *str, char *s2)
{
	free(str);
	str = NULL;
	if (s2)
	{
		str = ft_strdup(s2);
		free(s2);
		s2 = NULL;
	}
	else
		str = ft_strdup("");
	return (str);
}
