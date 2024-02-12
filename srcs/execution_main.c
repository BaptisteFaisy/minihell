/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:37:49 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/12 10:47:53 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution(t_cmd_args *cargs)
{
	t_exec_info	exec_info;

	init_t_exec_info(&exec_info);
	exec_info.paths = resolve_path(cargs->envp);
	if (exec_info.paths == NULL)
		return (EXEC_FAILURE);
	if (!init_redirect_files(cargs, &exec_info))
		return (EXEC_FAILURE); // TODO : free exec_info
	return (EXEC_SUCCESS);
}
