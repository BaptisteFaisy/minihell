/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:23:37 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/27 14:14:19 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*args;
	bool	n_flag;

	(void)info;
	args = cargs->args;
	n_flag = false;
	if (args && ft_strncmp((char *)args->content, "-n", 2) == 0)
	{
		n_flag = true;
		args = args->next;
	}
	while (args)
	{
		ft_putstr_fd((char *)args->content, 1);
		if (args->next)
			ft_putchar_fd(' ', 1);
		args = args->next;
	}
	if (n_flag == false)
		ft_putchar_fd('\n', 1);
	return (EXEC_SUCCESS);
}
