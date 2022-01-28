/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:54:55 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/21 23:21:37 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Fuction that convert an ascii numbers to an int

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	count;
	int	res;

	sign = 1;
	count = 0;
	res = 0;
	while (nptr[count] == ' ' || (nptr[count] >= 9 && nptr[count] <= 13))
		count++;
	if (nptr[count] == '-' || nptr[count] == '+')
	{
		if (nptr[count] == '-')
			sign = sign * -1;
		count++;
	}
	while (nptr[count] >= '0' && nptr[count] <= '9')
	{
		res = res * 10 + nptr[count] - '0';
		count++;
	}
	return (res * sign);
}
