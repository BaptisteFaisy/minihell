/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:30:42 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/01 15:46:41 by lhojoon          ###   ########.fr       */
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
		if (dup2(*(int *)ft_lstlast(info->redirect.red_in)->content, 0) == -1)
		{
			return (false);
		}
		ft_lstclear(&info->redirect.red_in, free_redirect_fd);
	}
	else if (prevfd[0] != -1)
	{
		if (dup2(prevfd[0], 0) == -1)
			return (false);
	}
	if (prevfd[1] != -1)
	{
		close(prevfd[1]);
		prevfd[1] = -1;
	}
	return (true);
}

static bool	output_redirect(t_exec_info *info, int curfd[2], int *stdout_cpy)
{
	if (stdout_cpy != NULL)
		*stdout_cpy = dup(1);
	if (info->redirect.red_out)
	{
		if (dup2(*(int *)ft_lstlast(info->redirect.red_out)->content, 1) == -1)
			return (false);
		ft_lstclear(&info->redirect.red_out, free_redirect_fd);
	}
	else if (curfd[1] != -1)
	{
		if (dup2(curfd[1], 1) == -1)
			return (false);
	}
	if (stdout_cpy != NULL)
		closefd(&curfd[0]);
	return (true);
}

static int	handle_execve(t_exec_info *info, char **envp_tmp, char **args_tmp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (info->cmd != NULL)
			status = execve(info->cmd, args_tmp, envp_tmp);
		else
			status = EXEC_FAILURE;
		free(envp_tmp);
		free(args_tmp);
		exit(status);
	}
	else
	{
		if (true || waitpid(-1, &status, 0) == -1)
			return (free(envp_tmp), free(args_tmp), EXEC_FAILURE);
	}
	free(envp_tmp);
	free(args_tmp);
	return (status);
}

// static int	redirect_fdvalue(int *fd)
// {
// 	dup2(1, *fd);
// 	close(*fd);
// }

/**
 * must close all file descriptors
*/
static int
	execution_child(t_cmd_args *cargs, t_exec_info *info,
					int prevfd[2], int curfd[2])
{
	int		exit_code;
	int		stdout_cpy;

	if (!init_redirect_files(cargs, info))
		return (EXEC_FAILURE); // TODO : free exec_info
	if (is_builtin(cargs->cmd) == true)
	{
		if (!input_redirect(info, prevfd)
			|| !output_redirect(info, curfd, &stdout_cpy))
			return (EXEC_FAILURE); // TODO : free exec_info
		info->cmd = ft_strdup(cargs->cmd);
		exit_code = exec_builtin(cargs, info);
		closefd(&curfd[1]);
		dup2(stdout_cpy, 1);
	}
	else
	{
		info->cmd = get_cmd(cargs, info);
		exit_code = handle_execve(info, transform_envp(cargs->envp),
				list_to_args(cargs->cmd, cargs->args));
	}
	return (exit_code); // TODO : free exec_info
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
			return (EXEC_FAILURE); // TODO : Error message, free all fds
		exit_code = execution_child(cargs, exec_info, prevfd, curfd);
		set_fd(prevfd, curfd[0], curfd[1]);
		cargs = cargs->next;
	}
	closefd(&prevfd[1]);
	print_final_output(prevfd[0]);
	return (exit_code);
}
