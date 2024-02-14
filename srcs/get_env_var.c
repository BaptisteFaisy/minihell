/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:50:20 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/14 12:51:36 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *envp[], char *varname)
{
	while (*envp && ft_strncmp(varname, *envp, ft_strlen(varname)))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + ft_strlen(varname));
}
