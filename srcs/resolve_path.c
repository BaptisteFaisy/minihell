/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:30:01 by lhojoon           #+#    #+#             */
/*   Updated: 2024/04/02 15:45:03 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_str(t_list *envp)
{
	while (envp && ft_strncmp("PATH", (char *)envp->content, 4))
		envp = envp->next;
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
