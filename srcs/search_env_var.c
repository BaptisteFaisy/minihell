/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:23:35 by marvin            #+#    #+#             */
/*   Updated: 2024/02/19 23:57:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*search_env_var(t_list *envp, char *var)
{
	while (envp)
	{
		if (ft_strncmp((char *)envp->content, var, ft_strlen(var)) == 0)
			return ((char *)envp->content);
		envp = envp->next;
	}
	return (NULL);
}
