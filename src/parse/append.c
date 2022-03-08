/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

char	*append(t_dollvar *data)
{
	char	*ret;

	if (!data->value && !data->ret && data->tmp)
	{
		ret = ft_strdup(data->tmp);
		free(data->tmp);
		data->tmp = NULL;
		return (ret);
	}
	else if (!data->value && data->ret && data->tmp)
	{
		ret = ft_strjoin(data->ret, data->tmp);
		free(data->ret);
		data->ret = NULL;
		return (ret);
	}
	else if (data->value && !data->ret && data->tmp)
		return (ft_strjoin(data->tmp, data->value));
	else if (!data->value && data->ret && !data->tmp)
		return (data->ret);
	return (append_next(data));
}

char	*append_next(t_dollvar *data)
{
	char	*ret;

	if (data->value && data->ret && !data->tmp)
	{
		ret = ft_strjoin(data->ret, data->value);
		free(data->ret);
		data->ret = NULL;
		return (ret);
	}
	else if (data->value && !data->ret && !data->tmp)
	{
		ret = ft_strdup(data->value);
		free(data->value);
		data->value = NULL;
		return (ret);
	}
	return (NULL);
}
