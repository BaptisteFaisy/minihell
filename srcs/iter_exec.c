/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:30:42 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 19:12:20 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!info->cmd)
		{
			if (!cargs->cmd)
				return (close_two_fds(info), EXEC_SUCCESS);
			return (close_two_fds(info),
				basherr(cargs->cmd, ERR_CMD_NOT_FOUND), EXEC_CMD_NFD);
		}
		exit_code = handle_execve(info, transform_envp(cargs->envp),
				list_to_args(cargs->cmd, cargs->args));
	}
	return (close_two_fds(info), exit_code);
}

static bool	pipe_init(int curfd[2], bool is_end)
{
	if (is_end)
	{
		curfd[0] = -1;
		curfd[1] = -1;
		return (true);
	}
	if (pipe(curfd) == -1)
	{
		basherr(NULL, ERR_PIPE);
		return (false);
	}
	return (true);
}

static void	iter_exec_init(int prevfd[2], int *exit_code, int *final_status)
{
	set_fd(prevfd, -1, -1);
	*exit_code = EXIT_SUCCESS;
	*final_status = EXIT_SUCCESS;
}

int	iter_exec(t_cmd_args *cargs, char **paths)
{
	int				prevfd[2];
	int				curfd[2];
	t_exec_info		*exec_info;
	int				exit_code;
	int				final_status;

	iter_exec_init(prevfd, &exit_code, &final_status);
	while (cargs)
	{
		exit_code = set_exec_info(&exec_info, NULL, cargs, paths);
		if (exit_code != EXEC_SUCCESS)
			return (exit_code);
		if (!pipe_init(curfd, cargs->next == NULL))
			return (free(exec_info), closefd(&prevfd[0]), closefd(&prevfd[1]),
				basherr(NULL, ERR_PIPE), EXEC_FAILURE);
		exit_code = execution_child(cargs, exec_info, prevfd, curfd);
		if (exit_code != EXIT_SUCCESS)
			final_status = exit_code;
		set_fd(prevfd, curfd[0], curfd[1]);
		cargs = cargs->next;
		free_exec_info(exec_info);
	}
	print_final_output(prevfd[0]);
	return (final_status);
}
