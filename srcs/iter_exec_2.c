/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:13:37 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/27 14:02:11 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	print_final_output(int ifd)
// {
// 	char	*buf;

// 	buf = get_next_line(ifd);
// 	while (buf)
// 	{
// 		ft_putstr_fd(buf, 1);
// 		free(buf);
// 		buf = get_next_line(ifd);
// 	}
// }

// void	set_fd(int fdcontainer[2], int first, int next)
// {
// 	fdcontainer[0] = first;
// 	fdcontainer[1] = next;
// }

void	free_redirect_fd(void *content)
{
	int	fd;

// 	fd = *(int *)content;
// 	if (fd != -1)
// 		close(*(int *)content);
// 	free(content);
// }
