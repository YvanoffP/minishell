/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	detect_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 34 && str[i] != 39 && str[i])
		i++;
	if (str[i] == 34 || str[i] == 39)
		return (1);
	return (0);
}

int	check_dollar_validity(char *str, int i)
{
	int	init_i;

	init_i = i;
	if (ft_isdigit(str[i + 1]))
		return (1);
	i++;
	while (!is_w_space(str[i]) && str[i] != '=' && str[i]
		&& str[i] != 34 && str[i] != 39 && str[i] != '$')
		i++;
	if (init_i == i - 1)
		return (0);
	else
		return (1);
}

void	fill_ret(int **ret)
{
	int	k;

	k = -1;
	while (++k < 100)
		*(*(ret) + k) = -1;
}

int	*have_a_dollar_out_q(char *str, int i)
{
	int	*ret;
	int	k;
	int flag;

	ret = malloc(sizeof(int) * 100);
	k = 0;
	flag = 0;
	fill_ret(&ret);
	while (str[i])
	{
		if (str[i] == 34 && flag == 0)
			flag = 1;
		else if (str[i] == 34 && flag == 1)
			flag = 0;
		if (str[i] == '$')
		{
			if (check_dollar_validity(str, i))
				ret[k++] = i;
		}
		else if (str[i] == 39 && flag == 0)
			skip_quote(str, &i);
		i++;
	}
	return (ret);
}
