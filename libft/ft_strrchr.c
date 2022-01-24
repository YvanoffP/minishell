/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:31:52 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/17 19:13:31 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		count;

	count = ft_strlen(s);
	if (count >= 0)
	{
		while (s[count] != (char)c && count > 0)
			count--;
		if (s[count] == (char)c)
			return ((char *)(s + count));
	}
	return (NULL);
}
