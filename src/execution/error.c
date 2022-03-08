/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_errs(t_errs *err)
{
	err->error = false;
	err->str_err = NULL;
	err->next = NULL;
	err->prev = NULL;
}

void	add_new_err_node(t_errs *err)
{
	t_errs	*new;

	new = malloc(sizeof(t_errs));
	init_errs(new);
	new->prev = err;
	err->next = new;
}

void	destroy_err(t_errs *err)
{
	t_errs	*tmp;

	while (err)
	{
		tmp = err->prev;
		free(err->str_err);
		free(err);
		err = tmp;
	}
}
