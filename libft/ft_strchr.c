/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:12:04 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/21 23:26:27 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Function who find an occurence of a char in a string
//then return a pointer to this occurence

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		count;
	char	*res;

	res = (char *)s;
	count = 0;
	while (s[count] != '\0')
	{
		if (s[count] == (char)c)
			return (res);
		count++;
		res++;
	}
	if (s[count] == (char)c)
		return (res);
	return (NULL);
}

/*int	main()
{
	const char s[] = "fiewofjjviowe";
	printf("Result = %s\n", strchr(s, 0));
	printf("Result = %s\n", ft_strchr(s, 0));
}*/
