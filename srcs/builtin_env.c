/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:33:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/27 14:13:26 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

int	builtin_env(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*lst;

	(void)info;
	lst = cargs->envp;
	while (lst)
	{
		ft_putendl_fd((char *)lst->content, STDOUT_FILENO);
		lst = lst->next;
	}
	return (EXEC_SUCCESS);
}