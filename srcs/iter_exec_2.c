/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:13:37 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/23 16:27:19 by lhojoon          ###   ########.fr       */
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

void	free_redirect_fd(void *content)
{
	int	fd;

	fd = *(int *)content;
	if (fd != -1)
		close(*(int *)content);
	free(content);
}

bool	add_pid(t_list **pids, pid_t pid)
{
	t_list	*new;
	pid_t	*ppid;

	if (pid == -1)
		return (perror(ERR_FORK), false);
	if (pid == 0)
		return (true);
	ppid = (pid_t *)malloc(sizeof(pid_t));
	if (!ppid)
		return (perror(ERR_MALLOC), false);
	*ppid = pid;
	new = ft_lstnew(ppid);
	if (!new)
		return (free(ppid), perror(ERR_MALLOC), false);
	ft_lstadd_back(pids, new);
	return (true);
}

int	wait_pid(t_list **pids)
{
	int		status;
	int		status_final;
	pid_t	pid;
	t_list	*tp;

	status_final = 0;
	tp = *pids;
	while (tp)
	{
		pid = *(pid_t *)(tp)->content;
		waitpid(pid, &status, 0);
		if (status != 0)
			status_final = status;
		kill(pid, SIGTERM);
		tp = tp->next;
	}
	ft_lstclear(pids, free);
	return (status_final);
}
