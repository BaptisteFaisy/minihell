/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:30:01 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/19 19:08:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_str(t_list *envp)
{
	while (envp && ft_strncmp("PATH", (char *)envp->content, 4))
		envp++;
	if (!envp)
		return (NULL);
	return ((char *)envp->content + 5);
}

char	**resolve_path(t_list *envp)
{
	char	*path_str;
	char	**paths;

	path_str = get_path_str(envp);
	if (!path_str)
		return (NULL);
	paths = ft_split(path_str, ':');
	return (paths);
}
