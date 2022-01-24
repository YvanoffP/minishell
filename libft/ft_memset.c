/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:57:38 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/21 23:36:32 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Function who fill a void type b by a char "c" for len times

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	count;

	count = 0;
	while (count < len)
	{
		((char *)b)[count] = c;
		count++;
	}
	return (b);
}
