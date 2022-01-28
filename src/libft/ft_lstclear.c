/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 21:32:00 by tpauvret          #+#    #+#             */
/*   Updated: 2021/10/16 22:08:23 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*keep;

	tmp = *lst;
	while (tmp)
	{
		keep = tmp->next;
		ft_lstdelone(tmp, (*del));
		tmp = keep;
	}
	*lst = NULL;
}
