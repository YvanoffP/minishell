/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:47:36 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/21 23:23:25 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Function who return the last cells of a chained list

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;
	int	j;

	i = ft_lstsize(lst) - 1;
	j = 0;
	while (j < i)
	{
		j++;
		lst = lst->next;
	}
	return (lst);
}
