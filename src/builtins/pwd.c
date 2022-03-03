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
	char	*parsed_cwd;
	char	buff[4096];

	cwd = getcwd(buff, 4096);
	if (cwd == NULL)
		write(1, "pwd command failed\n", 19);
	parsed_cwd = sub_path(cwd);
	write(1, parsed_cwd, ft_strlen(parsed_cwd));
	write(1, "\n", 1);
	if (parsed_cwd)
		free(parsed_cwd);
}
