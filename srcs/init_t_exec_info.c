/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_exec_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:42:21 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 23:11:30 by lhojoon          ###   ########.fr       */
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
	var->oldsint = NULL;
	var->oldsquit = NULL;
	return (var);
}

int	set_exec_info(
		t_exec_info **info, char *cmd, t_cmd_args *cargs, char **paths)
{
	int	ret;

	*info = init_t_exec_info();
	if (!*info)
		return (EXEC_FAILURE);
	(*info)->cmd = cmd;
	(*info)->paths = paths;
	ret = init_redirect_files(cargs, *info);
	if (ret != 0)
		return (free(*info), ret);
	return (EXEC_SUCCESS);
}
