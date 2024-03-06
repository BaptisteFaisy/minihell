/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:30:42 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/05 18:10:40 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_execve(t_exec_info *info, char **envp_tmp,
		char **args_tmp, int *fds[2])
{
	pid_t	pid;
	int		status;

	if (!envp_tmp || !args_tmp)
		return (perror(ERR_MALLOC), EXEC_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		(void)fds;
		if (info->in_fd != -1 && info->in_fd != 0)
			dup2(info->in_fd, STDIN_FILENO);
		if (info->out_fd != -1 && info->out_fd != 1)
			dup2(info->out_fd, STDOUT_FILENO);
		if (info->cmd != NULL)
			execve(info->cmd, args_tmp, envp_tmp);
		else
			exit(EXEC_SUCCESS);
	}
	free(envp_tmp);
	free(args_tmp);
	if (waitpid(-1, &status, 0) == -1)
		return (EXEC_FAILURE);
	return (status);
}

/**
 * must close all file descriptors
*/
static int
	execution_child(t_cmd_args *cargs, t_exec_info *info,
					int prevfd[2], int curfd[2])
{
	int		exit_code;

	info->in_fd = get_input_fd(info, prevfd);
	info->out_fd = get_output_fd(info, curfd);
	if (is_builtin(cargs->cmd) == true)
	{
		info->cmd = ft_strdup(cargs->cmd);
		exit_code = exec_builtin(cargs, info);
	}
	else
	{
		info->cmd = get_cmd(cargs, info);
		exit_code = handle_execve(info, transform_envp(cargs->envp),
				list_to_args(cargs->cmd, cargs->args),
				(int *[2]){prevfd, curfd});
	}
	closefd(&info->in_fd);
	closefd(&info->out_fd);
	return (exit_code);
}

int	iter_exec(t_cmd_args *cargs, char **paths)
{
	int				prevfd[2];
	int				curfd[2];
	t_exec_info		*exec_info;
	int				exit_code;

	set_fd(prevfd, -1, -1);
	exit_code = EXIT_SUCCESS;
	while (cargs)
	{
		if (set_exec_info(&exec_info, NULL, cargs, paths) == false)
			return (EXEC_FAILURE);
		if (pipe(curfd) == -1)
			return (free(exec_info), EXEC_FAILURE); // TODO : Error message, free all fds
		exit_code = execution_child(cargs, exec_info, prevfd, curfd);
		if (exit_code != EXIT_SUCCESS)
			g_status = exit_code;
		set_fd(prevfd, curfd[0], curfd[1]);
		cargs = cargs->next;
		free_exec_info(exec_info);
	}
	print_final_output(prevfd[0]);
	return (exit_code);
}
