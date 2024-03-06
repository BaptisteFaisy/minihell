/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:11:43 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 19:34:23 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_execve_dup(t_exec_info *info)
{
	if (info->in_fd != -1 && info->in_fd != 0)
		dup2(info->in_fd, STDIN_FILENO);
	if (info->out_fd != -1 && info->out_fd != 1)
		dup2(info->out_fd, STDOUT_FILENO);
}

int	handle_execve(t_exec_info *info, char **envp_tmp,
		char **args_tmp)
{
	pid_t	pid;
	int		status;

	if (!envp_tmp || !args_tmp)
		return (perror(ERR_MALLOC), EXEC_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		handle_execve_dup(info);
		if (is_directory(info->cmd) == true)
			return (basherr(info->cmd, ERR_IS_DIR), exit(EXEC_IS_DIR), 0);
		if (info->cmd != NULL)
			execve(info->cmd, args_tmp, envp_tmp);
		else
			exit(EXEC_SUCCESS);
		if (errno)
			return (basherr(info->cmd, NULL),
				exit(EXEC_FAILURE), 0);
	}
	free(envp_tmp);
	free(args_tmp);
	if (waitpid(pid, &status, 0) == -1)
		return (EXEC_FAILURE);
	return (WEXITSTATUS(status));
}
