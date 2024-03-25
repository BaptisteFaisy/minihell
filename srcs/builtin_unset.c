/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:33:04 by marvin            #+#    #+#             */
/*   Updated: 2024/03/25 17:29:17 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_one_element_from_envp(t_list **envp, char *var)
{
	t_list	*prev;
	t_list	*curr;
	t_list	*tmp;

	prev = NULL;
	curr = *envp;
	while (curr)
	{
		if (ft_strncmp((char *)(*envp)->content, var, ft_strlen(var)) == 0)
		{
			tmp = curr->next;
			free(curr->content);
			free(curr);
			curr = tmp;
			if (prev != NULL)
				prev->next = curr;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	builtin_unset(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*args;

	(void)info;
	args = cargs->args;
	while (args)
	{
		remove_one_element_from_envp(&cargs->envp, (char *)args->content);
		args = args->next;
	}
	return (EXEC_SUCCESS);
}
