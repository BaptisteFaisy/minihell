/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:33:04 by marvin            #+#    #+#             */
/*   Updated: 2024/02/23 13:16:24 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	remove_one_element_from_envp(t_list **envp, char *var)
{
	t_list	*prev;

	prev = *envp;
	while (envp)
	{
		if (ft_strncmp((char *)(*envp)->content, var, ft_strlen(var)) == 0)
		{
			if (prev == *envp)
			{
				prev = (*envp)->next;
				free((*envp)->content);
				free(envp);
				*envp = prev;
			}
			else
			{
				prev->next = (*envp)->next;
				free((*envp)->content);
			}
			return (true);
		}
		prev = *envp;
		(*envp) = (*envp)->next;
	}
	return (true);
}

void	builtin_unset(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*args;

	(void)info;
	args = cargs->args;
	while (args)
	{
		remove_one_element_from_envp(&cargs->envp, (char *)args->content);
		args = args->next;
	}
	exit(EXEC_SUCCESS);
}
