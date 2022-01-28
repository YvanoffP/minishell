/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:58:27 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/12 12:01:48 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	i;
	size_t	len_src;
	size_t	len_dst;

	count = 0;
	len_dst = ft_strlen((char *)dst);
	len_src = ft_strlen((char *)src);
	i = len_dst;
	if (dstsize == 0)
		return (len_src);
	if (dstsize < len_dst)
		return (len_src + dstsize);
	else
	{
		while (src[count] && (len_dst + count) < dstsize)
			dst[i++] = src[count++];
		if ((len_dst + count) == dstsize && len_dst < dstsize)
			dst[--i] = '\0';
		else
			dst[i] = '\0';
		return (len_src + len_dst);
	}
}
