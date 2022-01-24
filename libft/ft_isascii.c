/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:55:28 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/11 19:11:50 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*int  main()
{
        printf("alnum ? %d\n", isascii('a'));
        printf("alnum ? %d\n", isascii('g'));
        printf("alnum ? %d\n", isascii('C'));
        printf("alnum ? %d\n", isascii('5'));
        printf("alnum ? %d\n", isascii('['));
        printf("alnum ? %d\n", isascii('	'));
        printf("alnum ? %d\n", ft_isascii('a'));
        printf("alnum ? %d\n", ft_isascii('g'));
        printf("alnum ? %d\n", ft_isascii('C'));
        printf("alnum ? %d\n", ft_isascii('5'));
        printf("alnum ? %d\n", ft_isascii('['));
        printf("alnum ? %d\n", isascii('	'));
}*/
