/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:02:14 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/05 18:01:15 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input_fd(t_exec_info *info, int prevfd[2])
{
	int	fd;

	fd = STDIN_FILENO;
	if (info->redirect.red_in)
	{
		closefd(&prevfd[0]);
		fd = *(int *)ft_lstlast(info->redirect.red_in)->content;
		ft_lstclear(&info->redirect.red_in, free_redirect_fd);
	}
	else if (prevfd[0] != -1)
	{
		fd = prevfd[0];
	}
	return (fd);
}

int	get_output_fd(t_exec_info *info, int curfd[2])
{
	int	fd;

	fd = STDOUT_FILENO;
	if (info->redirect.red_out)
	{
		closefd(&curfd[1]);
		fd = *(int *)ft_lstlast(info->redirect.red_out)->content;
		ft_lstclear(&info->redirect.red_out, free_redirect_fd);
	}
	else if (curfd[1] != -1)
	{
		fd = curfd[1];
	}
	return (fd);
}