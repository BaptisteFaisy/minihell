/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:30:42 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/15 13:55:46 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @details Priority (for example cat)
 * 1. argument provided directly to command (ex. cat file.txt)
 * 2. redirection (ex. cat < file.txt) - last redirection will be used
 * 3. pipe (ex. echo "hello" | cat)
*/
static bool	input_redirect(t_exec_info *info, int prevfd[2])
{
	if (info->redirect.red_in)
	{
		dup2(*(int *)ft_lstlast(info->redirect.red_in)->content, 0);
		ft_lstclear(&info->redirect.red_in, free_redirect);
	}
	else if (prevfd[0] != -1)
		dup2(prevfd[0], 0);
	if (prevfd[1] != -1)
	{
		close(prevfd[1]);
		prevfd[1] = -1;
	}
	return (true);
}

static bool	output_redirect(t_exec_info *info, int curfd[2])
{
	if (info->redirect.red_out)
	{
		dup2(*(int *)ft_lstlast(info->redirect.red_out)->content, 1);
		ft_lstclear(&info->redirect.red_out, free_redirect);
	}
	else if (curfd[1] != -1)
		dup2(curfd[1], 1);
	if (curfd[0] != -1)
	{
		close(curfd[0]);
		curfd[0] = -1;
	}
	return (true);
}

/**
 * must close all file descriptors
*/
static int
	execution_child(t_cmd_args *cargs, t_exec_info *info,
					int prevfd[2], int curfd[2])
{
	if (!init_redirect_files(cargs, info))
		return (EXEC_FAILURE); // TODO : free exec_info
	input_redirect(info, prevfd);
	output_redirect(info, curfd);
	if (is_builtin(cargs->cmd))
	{
		ft_strlcpy(info->cmd, cargs->cmd, ft_strlen(cargs->cmd));
		exec_builtin(); // TODO : Do this
	}
	else
	{
		info->cmd = get_cmd(cargs, info);
		execve(info->cmd, cargs->args, cargs->envp);
	}
	return (EXEC_SUCCESS); // TODO : free exec_info
}

int	iter_exec(t_cmd_args *cargs, char **paths)
{
	t_list			*pids;
	int				prevfd[2];
	int				curfd[2];
	t_exec_info		*exec_info;
	pid_t			tpid;

	set_fd(prevfd, -1, -1);
	while (cargs)
	{
		if (set_exec_info(&exec_info, NULL, cargs, paths) == false)
			return (EXEC_FAILURE);
		if (pipe(curfd) == -1)
			return (EXEC_FAILURE); // TODO : Error message, free all fds
		tpid = fork();
		if (add_pid(&pids, tpid) == false)
			return (EXEC_FAILURE); // TODO : Error message, free all fds
		if (tpid == 0)
			execution_child(cargs, exec_info, prevfd, curfd);
		set_fd(prevfd, curfd[0], curfd[1]);
		cargs = cargs->next;
	}
	wait_pid(&pids);
	close(prevfd[1]);
	print_final_output(prevfd[0]);
	return (0);
}
