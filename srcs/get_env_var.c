/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:50:20 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/28 16:15:14 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(t_list *envp, char *varname)
{
	size_t	len;

	len = ft_strlen(varname);
	if (len > ft_strlen((char *)envp->content))
		len = ft_strlen((char *)envp->content);
	while (envp
		&& ft_strncmp(varname, (char *)envp->content, len) != 0)
		envp = envp->next;
	if (!envp)
		return (NULL);
	return ((char *)envp->content + ft_strlen(varname));
}
