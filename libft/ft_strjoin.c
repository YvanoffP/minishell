/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:22:13 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/21 23:27:52 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Function who join two string together on anoter one

#include "libft.h"

static char	*fill_string(char *ret, char const *s1, char const *s2, size_t ind);

static char	*fill_string(char *ret, char const *s1, char const *s2, size_t ind)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ind)
	{
		while (s1[i] != '\0')
		{
			ret[i] = s1[i];
			i++;
		}
		while (s2[j] != '\0')
		{
			ret[i] = s2[j++];
			i++;
		}
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	ind;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	ind = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (ind + 1));
	if (ret == NULL)
		return (NULL);
	return (fill_string(ret, s1, s2, ind));
}
