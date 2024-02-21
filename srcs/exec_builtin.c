/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:21:11 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/21 19:55:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_cmd_args *cargs, t_exec_info *info)
{
	if (ft_strncmp(info->cmd, "echo", 4) == 0)
		builtin_echo(cargs, info);
	else if (ft_strncmp(info->cmd, "cd", 2) == 0)
		builtin_cd(cargs, info);
	else if (ft_strncmp(info->cmd, "pwd", 3) == 0)
		builtin_pwd(cargs, info);
	else if (ft_strncmp(info->cmd, "export", 6) == 0)
		builtin_export(cargs, info);
	else if (ft_strncmp(info->cmd, "unset", 5) == 0)
		builtin_unset(cargs, info);
	else if (ft_strncmp(info->cmd, "env", 3) == 0)
		builtin_env(cargs, info);
	else
		exit(EXEC_FAILURE);
	return (0);
}
