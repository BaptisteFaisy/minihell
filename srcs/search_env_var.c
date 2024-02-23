/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:23:35 by marvin            #+#    #+#             */
/*   Updated: 2024/02/23 16:08:12 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_env_var(t_list *envp, char *var)
{
	while (envp)
	{
		if (ft_strncmp((char *)envp->content, var, ft_strlen(var)) == 0)
			return ((char *)envp->content);
		envp = envp->next;
	}
	return (NULL);
}
