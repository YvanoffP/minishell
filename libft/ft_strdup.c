/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:06:41 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/14 21:24:22 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size_src;
	int		c;
	char	*ret;

	size_src = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (size_src + 1));
	if (ret == NULL)
		return (NULL);
	c = 0;
	while (s1[c])
	{
		ret[c] = s1[c];
		c++;
	}
	ret[c] = '\0';
	return (ret);
}
