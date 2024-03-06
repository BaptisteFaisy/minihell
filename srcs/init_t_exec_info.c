/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_exec_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:42:21 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 18:17:40 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec_info	*init_t_exec_info(void)
{
	t_exec_info	*var;

	var = (t_exec_info *)malloc(sizeof(t_exec_info));
	if (!var)
		return (perror(ERR_MALLOC), NULL);
	var->cmd = NULL;
	var->redirect.red_in = NULL;
	var->redirect.red_out = NULL;
	var->paths = NULL;
	var->in_fd = -1;
	var->out_fd = -1;
	return (var);
}

bool	set_exec_info(
		t_exec_info **info, char *cmd, t_cmd_args *cargs, char **paths)
{
	*info = init_t_exec_info();
	if (!*info)
		return (false);
	(*info)->cmd = cmd;
	(*info)->paths = paths;
	if (init_redirect_files(cargs, *info) == false)
		return (free(*info), false);
	return (true);
}
