/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:13:37 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 02:04:04 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_final_output(int ifd)
{
	char	*buf;

	buf = get_next_line(ifd);
	while (buf)
	{
		ft_putstr_fd(buf, 1);
		free(buf);
		buf = get_next_line(ifd);
	}
}

void	set_fd(int fdcontainer[2], int first, int next)
{
	fdcontainer[0] = first;
	fdcontainer[1] = next;
}

void	free_redirect_fd_except_last(t_list *lst)
{
	int		fd;
	t_list	*tmp;

	while (lst)
	{
		fd = *(int *)lst->content;
		if (fd != -1 && lst->next != NULL)
			close(*(int *)lst->content);
		free(lst->content);
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void	closefd(int *fd)
{
	if (*fd != -1 && *fd != 0 && *fd != 1)
	{
		close(*fd);
		*fd = -1;
	}
}
