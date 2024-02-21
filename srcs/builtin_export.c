/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:08:56 by marvin            #+#    #+#             */
/*   Updated: 2024/02/21 19:46:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_string_value(char *str)
{
	char	*retstr;

	if (ft_strchr(str, '=') == 0)
		retstr = ft_strjoin(str, "=");
	else
		retstr = ft_strdup(str);
	return (retstr);
}

static void	replace_existing_envp(t_list *args, t_list *envp, bool *exist)
{
	exist = true;
	free(envp->content);
	envp->content = ft_strdup(args->content);
}

// TODO : do key value
void	builtin_export(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*args;
	t_list	*envp;
	bool	exist;

	args = cargs->args;
	while (args)
	{
		exist = false;
		envp = cargs->envp;
		while (envp)
		{
			if (ft_strncmp((char *)args->content, (char *)envp->content,
					ft_strlen((char *)args->content)) == 0)
			{
				replace_existing_envp(args, envp, &exist);
				break ;
			}
			envp = envp->next;
		}
		if (!exist)
			ft_lstadd_back(&cargs->envp,
				ft_lstnew(get_string_value((char *)args->content)));
		args = args->next;
	}
	exit(EXIT_SUCCESS);
}
