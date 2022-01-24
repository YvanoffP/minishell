/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:08:51 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/14 23:10:20 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*ret;
	size_t		i;

	i = 0;
	ret = (char *)malloc(count * size);
	if (ret == NULL)
		return (NULL);
	while (i < count * size)
	{
		((char *)ret)[i] = '\0';
		i++;
	}
	return ((void *)ret);
}
