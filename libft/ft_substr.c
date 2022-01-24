/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:47:14 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/21 23:30:44 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Functon who create a new string
//She take an existing string, a start and a size
//then copy the string s on an other, starting at "start"
//for a maximum lenght "len"

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	count;

	count = 0;
	i = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((size_t)start > i)
		return (ft_strdup(""));
	if (i - start < len)
		len = i - (size_t)start;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	while (count < len)
	{
		ret[count] = s[start + count];
		count++;
	}
	ret[count] = '\0';
	return (ret);
}
