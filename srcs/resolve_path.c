/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:30:01 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/12 18:11:56 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_str(char *envp[])
{
	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + 5);
}

char	**resolve_path(char *envp[])
{
	char	*path_str;
	char	**paths;

	path_str = get_path_str(envp);
	if (!path_str)
		return (NULL);
	paths = ft_split(path_str, ':');
	return (paths);
}
