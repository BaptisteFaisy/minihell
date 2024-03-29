/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:13:38 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 18:18:08 by lhojoon          ###   ########.fr       */
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
	free(info);
}
