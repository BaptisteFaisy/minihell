/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:38:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/04 18:19:48 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : Verify if I have to verify cmd itself (ex. if /usr/bin/echo is received as command...)
char	*get_cmd(t_cmd_args *cargs, t_exec_info *info)
{
	char	*c;
	char	**paths;

	paths = info->paths;
	if (ft_strncmp(cargs->cmd, "./", 2) == 0)
	{
		c = ft_strjoin_many(3,
				get_env_var(cargs->envp, "HOME"), "/", cargs->cmd);
		if (access(c, 0) == 0)
			return (c);
		else
			return (free(c), NULL);
	}
	c = ft_strdup(cargs->cmd);
	if (access(c, 0) == 0)
		return (c);
	free(c);
	while (*paths)
	{
		c = ft_strjoin_many(3, *paths, "/", cargs->cmd);
		if (access(c, 0) == 0)
			return (c);
		free(c);
		paths++;
	}
	return (NULL);
}
