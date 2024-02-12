/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:38:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/12 18:36:03 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_str(char *envp[])
{
	while (*envp && ft_strncmp("HOME", *envp, 4))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + 5);
}

// TODO : Verify if I have to verify cmd itself (ex. if /usr/bin/echo is received as command...)
char	*get_cmd(t_cmd_args *cargs, t_exec_info *info)
{
	char	*tmp;
	char	*c;
	char	**paths;

	paths = info->paths;
	tmp = get_home_str(cargs->envp);
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
