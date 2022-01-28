/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 23:55:01 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/21 23:22:05 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Function that convert an int to a string of numbers

static int	ft_size_nbr(int nbr);
static char	*ft_fill_string(char *ret, int n, int size, int sign);

static int	ft_size_nbr(int nbr)
{
	int	size;

	size = 0;
	if (nbr < 0)
	{
		size++;
		nbr = nbr * -1;
	}
	while (nbr >= 1)
	{
		size++;
		nbr = nbr / 10;
	}
	return (size);
}

static char	*ft_fill_string(char *ret, int n, int size, int sign)
{
	if (n < 0)
	{
		sign++;
		n = n * -1;
	}
	ret[size] = '\0';
	while (--size)
	{
		ret[size] = (n % 10) + '0';
		n = n / 10;
	}
	if (sign != 0)
		ret[0] = '-';
	else
		ret[0] = (n % 10) + '0';
	return (ret);
}

char	*ft_itoa(int n)
{
	int		size;
	int		sign;
	char	*ret;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = ft_size_nbr(n);
	sign = 0;
	if (n != 0)
		ret = (char *)malloc(sizeof(char) * (size + 1));
	else
		return (ret = ft_strdup("0"));
	if (ret == NULL)
		return (NULL);
	else
		return (ft_fill_string(ret, n, size, sign));
}
