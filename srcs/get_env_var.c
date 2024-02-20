/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:50:20 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/19 19:07:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(t_list *envp, char *varname)
{
	while (envp
		&& ft_strncmp(varname, (char *)envp->content, ft_strlen(varname)))
		envp++;
	if (!envp)
		return (NULL);
	return ((char *)envp->content + ft_strlen(varname));
}
