/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:21:44 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/21 23:29:39 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Function who find occurence of a string in another string
//return a pointer on this occurence

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		count;
	size_t		n;

	count = 0;
	n = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[count] != '\0' && count < len)
	{
		n = 0;
		while (needle[n] == haystack[count + n]
			&& needle[n] != '\0'
			&& count + n < len)
			n++;
		if (n == (size_t)ft_strlen(needle))
			return ((char *)(haystack + count));
		count++;
	}
	return (NULL);
}

/*int	main()
{
	const char s[] = "mama le musty d'yvan sur rock ro rocket league rocketlea";
	const char s2[] = "rocketle";
	
	printf("Result normal : %s\n", strnstr(s, s2, 300));
	printf("Result mienne : %s\n", ft_strnstr(s, s2, 300));
}*/
