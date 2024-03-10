/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:33:54 by marvin            #+#    #+#             */
/*   Updated: 2024/03/09 09:11:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*lst;

	(void)info;
	lst = cargs->envp;
	while (lst)
	{
		if (ft_strchr((char *)lst->content, '=') != NULL)
			ft_putendl_fd((char *)lst->content, info->out_fd);
		lst = lst->next;
	}
	return (EXEC_SUCCESS);
}
