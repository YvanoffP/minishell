/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:56:56 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/21 23:34:00 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Function who search occurence and return a pointer at the occurence on s

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		if (((unsigned char *)s)[count] == (unsigned char)c)
			return ((void *)(s + count));
		count++;
	}
	return (NULL);
}

/*int main()
{
        char s[] = "salutest";

        printf("%s\n", (char*)memchr(s, 97, 5));
        printf("%s\n", (char*)ft_memchr(s, 97, 5));
}*/
