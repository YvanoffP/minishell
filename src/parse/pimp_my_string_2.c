/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pimp_my_string_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_missing_space(char *str, int *sep)
{
	int	i;
	int	*ptr;
	int	missing_space;

	missing_space = 0;
	i = 0;
	ptr = sep;
	while (*ptr)
	{
		i = *ptr;
		if (is_w_space(str[i - 1]))
			missing_space++;
		if (is_w_space(str[i + 1]))
			missing_space++;
		ptr++;
	}
	return (missing_space);
}

void	work_nb_n_len(int *nb_space, int *len)
{
	*nb_space += 1;
	*len -= 1;
}

char	*check_around_n_cpy(t_mini *shell, int *ptr, int i, int j)
{
	char	*ret;

	skip_w_space(shell->argv, &i);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(shell->argv)
				+ count_missing_space(shell->argv, ptr - i) + 1));
	if (!ret)
		return (NULL);
	while (shell->argv[i])
	{
		ret[j++] = shell->argv[i++];
		if (is_sep(shell->argv[i]) && shell->argv[i] && i == *ptr)
		{
			if (!is_w_space(shell->argv[i - 1]))
				ret[j++] = 32;
		}
		else if (is_sep(shell->argv[i - 1]) && shell->argv[i]
			&& ((i - 1) == *ptr || (i - 2) == *ptr) && !is_sep(shell->argv[i]))
		{
			if (!is_w_space(shell->argv[i]))
				ret[j++] = 32;
			ptr++;
		}
	}
	ret[j] = 0;
	return (ret);
}
