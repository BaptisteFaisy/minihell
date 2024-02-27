/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:21:11 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/27 14:11:43 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

int	exec_builtin(t_cmd_args *cargs, t_exec_info *info)
{
	if (ft_strncmp(info->cmd, "echo", 4) == 0)
		return (builtin_echo(cargs, info));
	else if (ft_strncmp(info->cmd, "cd", 2) == 0)
		return (builtin_cd(cargs, info));
	else if (ft_strncmp(info->cmd, "pwd", 3) == 0)
		return (builtin_pwd(cargs, info));
	else if (ft_strncmp(info->cmd, "export", 6) == 0)
		return (builtin_export(cargs, info));
	else if (ft_strncmp(info->cmd, "unset", 5) == 0)
		return (builtin_unset(cargs, info));
	else if (ft_strncmp(info->cmd, "env", 3) == 0)
		return (builtin_env(cargs, info));
	else
		return (EXEC_FAILURE);
}
