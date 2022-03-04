/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pimp_my_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	spaces_to_del(char *str)
{
	int		i;
	int		total;
	char	quote;

	i = -1;
	total = 0;
	while (str[++i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			quote = str[i++];
			while (str[i] != quote && str[i])
				i++;
		}
		else if (str[i] == 32)
		{
			i++;
			while (str[i] == 32 && str[i])
			{
				total++;
				i++;
			}
		}
	}
	return (total);
}

char	*pimp_my_string(t_mini *shell, int *sep)
{
	int		*ptr;
	char	*ret;
	t_alloc	var;

	var.i = 0;
	ptr = sep;
	ret = check_around_n_cpy(shell, ptr, 0, 0);
	delete_last_spaces(&ret);
	delete_mid_spaces(&ret, var);
	free(shell->argv);
	return (ret);
}

static void	init_alloc_var(t_alloc *var)
{
	var->i = 0;
	var->k = 0;
}

void	delete_mid_spaces(char **ret, t_alloc var)
{
	init_alloc_var(&var);
	var.ret = malloc(sizeof(char)
			* (ft_strlen(*ret) + spaces_to_del(*ret)) + 1);
	while ((*ret)[var.i])
	{
		if ((*ret)[var.i] == 39 || (*ret)[var.i] == 34)
		{
			var.ret[var.k++] = (*ret)[var.i];
			var.quote = (*ret)[var.i++];
			while ((*ret)[var.i] != var.quote)
				var.ret[var.k++] = (*ret)[var.i++];
			var.ret[var.k++] = (*ret)[var.i++];
		}
		else if ((*ret)[var.i] == 32)
		{
			var.ret[var.k++] = (*ret)[var.i++];
			skip_w_space(*ret, &var.i);
		}
		else
			var.ret[var.k++] = (*ret)[var.i++];
	}
	var.ret[var.k] = '\0';
	free(*ret);
	*ret = var.ret;
}

void	delete_last_spaces(char **str)
{
	int		len;
	int		i;
	int		nb_space;
	char	*tmp;

	len = ft_strlen(*str) - 1;
	tmp = NULL;
	i = -1;
	nb_space = 0;
	while (is_w_space((*str)[len]))
		work_nb_n_len(&nb_space, &len);
	if (nb_space)
	{
		tmp = malloc(sizeof(char) * (len + 2));
		if (!tmp)
			return ;
		while (i++ < len)
			tmp[i] = (*str)[i];
		tmp[i] = 0;
		free(*str);
		*str = ft_strdup(tmp);
		free(tmp);
	}
}
