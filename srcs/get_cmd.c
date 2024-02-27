/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:38:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/19 19:10:04 by marvin           ###   ########.fr       */
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
	tmp = get_env_var(cargs->envp, "HOME");
	c = ft_strjoin_many(3, tmp, "/", cargs->cmd);
	if (access(c, 0) == 0)
		return (c);
	free(c);
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
