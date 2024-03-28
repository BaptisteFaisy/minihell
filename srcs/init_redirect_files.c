/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirect_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:06:04 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/28 13:35:58 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	iter_redirect_input(t_list *details, t_list **infos)
{
	int		fd;
	int		*pfd;

	*infos = NULL;
	while (details)
	{
		if (((t_red_details *)details->content)->type == RED_IN_DELIM)
			fd = get_file_by_prompt_delim(
					((t_red_details *)details->content)->file);
		else
			fd = redirect_open(((t_red_details *)details->content)->file,
					R_OK, O_RDONLY);
		if (fd < 1)
			return (ft_lstclear(infos, free), -fd);
		pfd = (int *)malloc(sizeof(int));
		if (!pfd)
			return (ft_lstclear(infos, free),
				basherr(NULL, ERR_MALLOC), EXEC_FAILURE);
		*pfd = fd;
		ft_lstadd_back(infos, ft_lstnew(pfd));
		details = details->next;
	}
	return (0);
}

static int	iter_redirect_output(t_list *details, t_list **infos)
{
	int	fd;
	int	*pfd;

	*infos = NULL;
	while (details)
	{
		if (((t_red_details *)details->content)->type == RED_OUT_APPEND)
			fd = redirect_open(
					((t_red_details *)details->content)->file,
					W_OK | F_SKIP_NUL,
					O_WRONLY | O_CREAT | O_APPEND);
		else
			fd = redirect_open(((t_red_details *)details->content)->file,
					W_OK | F_SKIP_NUL, O_WRONLY | O_CREAT | O_TRUNC);
		if (fd < 1)
			return (ft_lstclear(infos, free), -fd);
		pfd = (int *)malloc(sizeof(int));
		if (!pfd)
			return (ft_lstclear(infos, free),
				basherr(NULL, ERR_MALLOC), EXEC_FAILURE);
		*pfd = fd;
		ft_lstadd_back(infos, ft_lstnew(pfd));
		details = details->next;
	}
	return (0);
}

static void	free_redirect(void *content)
{
	if (*(int *)content != -1)
		close((*(int *)content));
	free(content);
}

int	init_redirect_files(t_cmd_args *cargs, t_exec_info *info)
{
	t_red_info		red_info;
	int				ret;

	red_info = convert_red_info(cargs->redirect);
	ret = iter_redirect_input(red_info.red_in, &info->redirect.red_in);
	ft_lstclear(&red_info.red_in, free);
	if (ret != 0)
		return (ft_lstclear(&red_info.red_out, free), ret);
	ret = iter_redirect_output(red_info.red_out, &info->redirect.red_out);
	if (ret != 0)
		return (ft_lstclear(&info->redirect.red_in, free_redirect),
			ft_lstclear(&red_info.red_out, free), ret);
	return (ft_lstclear(&red_info.red_out, free), 0);
}
