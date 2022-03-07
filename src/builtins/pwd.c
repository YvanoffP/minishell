/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*cwd;
	char	buff[4096];

	cwd = getcwd(buff, 4096);
	if (cwd == NULL)
		write(1, "pwd command failed\n", 19);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
}
