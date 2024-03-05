/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:13:38 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/04 18:27:12 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec_info(t_exec_info *info)
{
	if (info->cmd)
	{
		free(info->cmd);
		info->cmd = NULL;
	}
	// if (info->redirect.red_in)
	// 	ft_lstclear(&info->redirect.red_in, free);
	// if (info->redirect.red_out)
	// 	ft_lstclear(&info->redirect.red_out, free);
	// if (info->paths)
	// 	ft_lstclear(&info->paths, free);
	free(info);
}
