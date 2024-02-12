/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirect_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:06:04 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/12 18:50:29 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_error(char *err)
// {
// 	char	*s;

// 	s = ft_strjoin_many(3, SHELL_NAME, ": ", err);
// 	perror(s);
// 	free(s);
// }

// static bool	iter_redirect_file(t_list *files,
// 			t_list **infos, int aflag, int oflag)
// {
// 	int	fd;
// 	int	*pfd;

// 	while (files)
// 	{
// 		fd = redirect_open((char *)files->content, aflag, oflag);
// 		if (fd < 0)
// 			return (ft_lstclear(infos, free), false);
// 		pfd = (int *)malloc(sizeof(int));
// 		if (!pfd)
// 			return (ft_lstclear(infos, free), print_error(ERR_MALLOC), false);
// 		*pfd = fd;
// 		ft_lstadd_back(infos, ft_lstnew(pfd));
// 		files = files->next;
// 	}
// 	return (true);
// }

// bool	init_redirect_files(t_cmd_args *cargs, t_exec_info *info)
// {
// 	if (iter_redirect_file(cargs->redirect.red_in, &info->redirect.red_in,
// 			F_OK, O_RDONLY) == false)
// 		return (false);
// 	if (iter_redirect_file(cargs->redirect.red_out, &info->redirect.red_out,
// 			F_OK, O_WRONLY | O_CREAT | O_TRUNC) == false)
// 		return (ft_lstclear(info->redirect.red_in, free), false);
// 	if (iter_redirect_file(cargs->redirect.red_in_delim,
// 			&info->redirect.red_in_delim, F_OK, O_WRONLY | O_CREAT | O_APPEND)
// 		== false)
// 		return (ft_lstclear(info->redirect.red_in, free),
// 			ft_lstclear(info->redirect.red_out, free), false);
// 	if (iter_redirect_file(cargs->redirect.red_out_append,
// 			&info->redirect.red_out_append, F_OK, O_WRONLY | O_CREAT | O_APPEND)
// 		== false)
// 		return (ft_lstclear(info->redirect.red_in, free),
// 			ft_lstclear(info->redirect.red_out, free),
// 			ft_lstclear(info->redirect.red_in_delim, free), false);
// 	return (true);
// }
