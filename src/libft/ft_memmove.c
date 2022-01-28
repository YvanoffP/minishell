/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:57:24 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/11 19:13:01 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dstc;
	const unsigned char	*srcc;

	dstc = (unsigned char *)dst;
	srcc = (const unsigned char *)src;
	if (dst == src)
		return (dst);
	if (srcc < dstc)
	{
		while (len != 0)
		{
			len--;
			*(dstc + len) = *(srcc + len);
		}
		return (dst);
	}
	while (len != 0)
	{
		len--;
		*dstc++ = *srcc++;
	}
	return (dst);
}

/*int main()
{
	unsigned char d[] = "gvedgfefqezfzefe";
	const unsigned char s[] = "salutest";

	printf("%s\n", (char*)memmove(d, s, 7));
	printf("%s\n", (char*)ft_memmove(d, s, 7));
}*/
