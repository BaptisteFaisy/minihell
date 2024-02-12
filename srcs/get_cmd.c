/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:38:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/12 10:53:12 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : Verify if I have to verify cmd itself (ex. if /usr/bin/echo is received as command...)
char	*get_cmd(t_cmd_args *cargs, t_exec_info *info)
{
	char	*tmp;
	char	*c;
	char	**paths;

	paths = info->paths;
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		c = ft_strjoin(tmp, cargs->cmd);
		free(tmp);
		if (access(c, 0) == 0)
			return (c);
		free(c);
		paths++;
	}
	return (NULL);
}
