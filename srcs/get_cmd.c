/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:38:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 18:14:40 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(t_cmd_args *cargs, t_exec_info *info)
{
	char	*c;
	char	**paths;

	paths = info->paths;
	if (cargs->cmd == NULL)
		return (NULL);
	if (ft_strncmp(cargs->cmd, "./", 2) == 0)
	{
		c = ft_strjoin_many(3,
				get_env_var(cargs->envp, "PWD"), "/", cargs->cmd + 2);
		if (access(c, 0) == 0)
			return (c);
		return (free(c), NULL);
	}
	if (ft_strncmp(cargs->cmd, "/", 1) == 0 && access(cargs->cmd, 0) == 0)
		return (ft_strdup(cargs->cmd));
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
