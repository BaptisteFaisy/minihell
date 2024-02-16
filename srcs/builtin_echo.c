/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:23:37 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/16 15:49:13 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*args;
	bool	n_flag;

	args = cargs->args;
	n_flag = false;
	if (ft_strncmp((const char *)args->content, "-n", 2) == 0)
	{
		n_flag = true;
		args = args->next;
	}
	while (args)
	{
		ft_putstr_fd((const char *)args->content, 1);
		args = args->next;
	}
	if (n_flag == true)
		ft_putchar_fd('\n', 1);
	exit(EXEC_SUCCESS);
}
