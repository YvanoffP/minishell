/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:55:13 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/11 19:11:33 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/*int	main()
{
	printf("alnum ? %d\n", isalnum('a'));
	printf("alnum ? %d\n", isalnum('g'));
	printf("alnum ? %d\n", isalnum('C'));
	printf("alnum ? %d\n", isalnum('5'));
	printf("alnum ? %d\n", isalnum('['));
	printf("alnum ? %d\n", ft_isalnum('a'));
	printf("alnum ? %d\n", ft_isalnum('g'));
	printf("alnum ? %d\n", ft_isalnum('C'));
	printf("alnum ? %d\n", ft_isalnum('5'));
	printf("alnum ? %d\n", ft_isalnum('['));
}*/
