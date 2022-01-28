/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:33:22 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/21 23:32:44 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Function who trim a string at the beginning and at the end
//the return is the string without "set" at the beginning and the end
//if this "set" was found

#include "libft.h"

static int	ft_is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (0);
		set++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	count;
	size_t	finish;
	char	*ret;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	finish = ft_strlen(s1);
	count = 0;
	while (ft_is_in_set(s1[count], set) == 0)
		count++;
	if (count == finish)
		return (ft_strdup(""));
	while (ft_is_in_set(s1[finish - 1], set) == 0)
		finish--;
	ret = ft_substr(s1, count, (finish - count));
	return (ret);
}
