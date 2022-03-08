/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_dollvar(t_dollvar *data, int i)
{
	data->j = i;
	data->ret = NULL;
	data->value = NULL;
	data->tmp = NULL;
	data->flag = 1;
	data->status = g_status.status;
}

static void	get_value_in_str_bis(t_dollvar *data)
{
	data->ret = append(data);
	if (data->tmp != NULL)
		free(data->tmp);
	if (data->value != NULL)
		free(data->value);
	data->tmp = NULL;
	data->value = NULL;
}

int	get_value_in_str(char *str, int *i, t_dollvar *data, t_env **env_list)
{
	if (str[*i + 1] == 34 || str[*i + 1] == '\0')
		return (0);
	if (str[*i + 1] == '?')
	{
		data->value = ft_itoa(data->status);
		*i += 2;
	}
	else
		data->value = find_env_var(str, i, env_list);
	if (!data->value)
	{
		data->ret = append(data);
		if (data->tmp != NULL)
			free(data->tmp);
		data->tmp = NULL;
	}
	else
		get_value_in_str_bis(data);
	data->j = *i;
	return (1);
}

int	find_dollars_str(char *str, int *i, t_dollvar *data, t_env **env_list)
{
	if (str[*i] == '$')
	{
		if (!get_value_in_str(str, i, data, env_list))
			return (0);
	}
	while (str[*i] != 34 && str[*i] != '$' && str[*i])
		*i += 1;
	if (data->flag)
	{
		while (str[*i])
			*i += 1;
	}
	if (*i != data->j)
	{
		data->value = ft_substr(str, data->j, *i - data->j);
		data->ret = append(data);
		free(data->tmp);
		free(data->value);
		data->tmp = NULL;
		data->value = NULL;
	}
	return (1);
}

char	*replace_dollars(char *str, t_env **env_list, int *i)
{
	t_dollvar	data;

	init_dollvar(&data, *i);
	if (*i != 0)
		data.tmp = ft_substr(str, 0, *i);
	while (str[*i] != 34 && str[*i])
	{
		if (!find_dollars_str(str, i, &data, env_list))
		{
			data.ret = ft_strdup("");
			*i = -10;
			break ;
		}
	}
	if (*i < (int)ft_strlen(str))
	{
		if (data.ret && data.tmp)
			data.tmp = ft_strjoin(data.tmp, data.ret);
		else
			data.tmp = ft_strdup(data.ret);
		replace_dollars_ext(&data, str, i);
	}
	return (data.ret);
}
