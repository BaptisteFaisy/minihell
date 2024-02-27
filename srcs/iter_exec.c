/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:30:42 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/27 14:56:49 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

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
		ft_lstclear(&info->redirect.red_in, free_redirect_fd);
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
		ft_lstclear(&info->redirect.red_out, free_redirect_fd);
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

static int	handle_execve(t_exec_info *info, char **envp_tmp, char **args_tmp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		status = execve(info->cmd, args_tmp, envp_tmp);
		exit(status);
	}
	else
	{
		if (waitpid(0, &status, 0) == -1)
			return (EXEC_FAILURE);
	}
	return (status);
}

/**
 * must close all file descriptors
*/
static int
	execution_child(t_cmd_args *cargs, t_exec_info *info,
					int prevfd[2], int curfd[2])
{
	char	**envp_tmp;
	char	**args_tmp;
	int		exit_code;

	if (!init_redirect_files(cargs, info))
		return (EXEC_FAILURE); // TODO : free exec_info
	if (is_builtin(cargs->cmd))
	{
		info->cmd = ft_strdup(cargs->cmd);
		exit_code = exec_builtin(cargs, info);
	}
	else
	{
		input_redirect(info, prevfd);
		output_redirect(info, curfd);
		info->cmd = get_cmd(cargs, info);
		envp_tmp = transform_envp(cargs->envp);
		args_tmp = list_to_args(cargs->cmd, cargs->args);
		exit_code = handle_execve(info, envp_tmp, args_tmp);
		free(envp_tmp);
		free(args_tmp);
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
	close(prevfd[1]);
	return (print_final_output(prevfd[0]), exit_code);
}
