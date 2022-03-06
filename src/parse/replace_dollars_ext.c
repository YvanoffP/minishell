/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars_ext.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	replace_dollars_ext(t_dollvar *data, char *str, int *i)
{
	data->value = ft_substr(str, *i, ft_strlen(str) - *i);
	free(data->ret);
	data->ret = NULL;
	data->ret = ft_strjoin(data->tmp, data->value);
	free(data->tmp);
	free(data->value);
	data->tmp = NULL;
	data->value = NULL;
}
