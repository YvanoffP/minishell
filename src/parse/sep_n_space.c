/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_n_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	detect_sep(char *str, int *start)
{
	if (str[*start] == '>')
	{
		if (str[*start + 1] == '>')
		{
			*start += 3;
			return (DB_GREAT);
		}
		*start += 2;
		return (GREAT);
	}
	else if (str[*start] == '<')
	{
		if (str[*start + 1] == '<')
		{
			*start += 3;
			return (DB_LESS);
		}
		*start += 2;
		return (LESS);
	}
	return (-1);
}

int	count_pipe(char *str)
{
	int		i;
	int		nb_sep;
	char	c;

	i = 0;
	nb_sep = 0;
	while (str[i])
	{
		skip_quote(str, &i);
		if (str[i] == '|')
		{
			nb_sep++;
			c = str[i];
			if (is_sep(str[i + 1]))
				return (-1);
		}
		i++;
	}
	return (nb_sep);
}

int	*parse_sep(char *str)
{
	int	nb_sep;
	int	*ind_sep;
	int	i;
	int	j;

	i = 0;
	j = 0;
	nb_sep = count_pipe(str);
	if (nb_sep == -1)
		return (NULL);
	ind_sep = malloc(sizeof(int) * nb_sep + 1);
	if (!ind_sep)
		return (NULL);
	while (str[i])
	{
		skip_quote(str, &i);
		if (str[i] == '|')
			ind_sep[j++] = i;
		i++;
	}
	ind_sep[j] = 0;
	return (ind_sep);
}

int	*parse_space(char *str)
{
	int	nb_space;
	int	*ind_space;
	int	i;
	int	j;

	i = 0;
	j = 0;
	nb_space = count_space(str);
	ind_space = malloc(sizeof(int) * nb_space + 1);
	if (!ind_space)
		return (NULL);
	ind_space[nb_space] = 0;
	while (str[i])
	{
		skip_quote(str, &i);
		if (is_w_space(str[i]))
		{
			ind_space[j++] = i;
			skip_w_space(str, &i);
			i--;
		}
		i++;
	}
	return (ind_space);
}

int	count_space(char *str)
{
	int	i;
	int	nb_space;

	i = 0;
	nb_space = 0;
	while (str[i])
	{
		skip_quote(str, &i);
		if (is_w_space(str[i]))
		{
			nb_space++;
			skip_w_space(str, &i);
			i--;
		}
		i++;
	}
	return (nb_space);
}
