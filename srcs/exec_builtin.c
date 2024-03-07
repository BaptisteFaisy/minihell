/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:21:11 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/07 18:04:40 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd_args *cargs, t_exec_info *info)
{
	if (ft_strncmp(info->cmd, "echo", 5) == 0)
		return (builtin_echo(cargs, info));
	else if (ft_strncmp(info->cmd, "cd", 3) == 0)
		return (builtin_cd(cargs, info));
	else if (ft_strncmp(info->cmd, "pwd", 4) == 0)
		return (builtin_pwd(cargs, info));
	else if (ft_strncmp(info->cmd, "export", 7) == 0)
		return (builtin_export(cargs, info));
	else if (ft_strncmp(info->cmd, "unset", 6) == 0)
		return (builtin_unset(cargs, info));
	else if (ft_strncmp(info->cmd, "env", 4) == 0)
		return (builtin_env(cargs, info));
	else if (ft_strncmp(info->cmd, "exit", 5) == 0)
		return (builtin_exit(cargs, info));
	else
		return (EXEC_FAILURE);
}
