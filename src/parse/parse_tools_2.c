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

void	skip_w_space(char *str, int *i)
{
	while (is_w_space(str[*i]))
		*i += 1;
}

int	have_a_dollar(char *str, int i)
{
	while (str[i] != 34 && str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	skip_quote(char *str, int *i)
{
	if (str[*i] == 34 || str[*i] == 39)
	{
		if (str[*i] == 34)
		{
			*i += 1;
			while (str[*i] != 34 && str[*i])
				*i += 1;
			if (!str[*i])
				return ;
		}
		else if (str[*i] == 39)
		{
			*i += 1;
			while (str[*i] != 39 && str[*i])
				*i += 1;
			if (!str[*i])
				return ;
		}
	}
}

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

int	have_a_dollar_out_q(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			skip_quote(str, &i);
			i++;
		}
		else if (str[i] == '$')
			return (i);
		else
			i++;
	}
	return (-1);
}
