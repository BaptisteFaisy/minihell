/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:30:42 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/13 21:13:56 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * must close all file descriptors
*/
static int
	execution_child(t_cmd_args *cargs, t_exec_info *info,
					int rfd, int wfd)
{
	if (!init_redirect_files(cargs, info))
		return (EXEC_FAILURE); // TODO : free exec_info
	info->cmd = get_cmd(cargs, info);
	// give last input redirection / in fd to 0, if not exist do not do anything
	execve(info->cmd, cargs->args, cargs->envp);
	// catch output and redirect to last out_redirection, if not exist to 1
	return (EXEC_SUCCESS);
}

int	iter_exec(t_cmd_args *cargs, t_exec_info *info)
{
	int	p;
	int	curfd[2];
	int	nextfd;
	int	tfd[2];

	curfd[1] = -1;
	while (cargs)
	{
		if (curfd[1] != -1)
			if (pipe(tfd) == -1)
				return (EXEC_FAILURE); // TODO : Error message
		curfd[0] = tfd[0];
		nextfd = tfd[1];
		p = fork();
		if (p == 0)
			execution_child(cargs, info, curfd[0], curfd[1]);
		else
			break ; // TODO : Verify this
		curfd[1] = nextfd;
		cargs = cargs->next;
	}
	dup2(curfd[1], 1);
	return (0);
}
