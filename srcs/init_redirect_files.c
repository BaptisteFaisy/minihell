/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirect_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:06:04 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/27 16:58:03 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *err)
{
	char	*s;

	s = ft_strjoin_many(3, SHELL_NAME, ": ", err);
	perror(s);
	free(s);
}

static bool	iter_redirect_input(t_list *details, t_list **infos)
{
	int	fd;
	int	*pfd;

	*infos = NULL;
	while (details)
	{
		if (((t_red_details *)details->content)->type == RED_IN_DELIM)
			fd = get_file_by_prompt_delim(
					((t_red_details *)details->content)->file);
		else
			fd = redirect_open(((t_red_details *)details->content)->file,
					R_OK, O_RDONLY);
		if (fd < 0)
			return (ft_lstclear(infos, free), false);
		pfd = (int *)malloc(sizeof(int));
		if (!pfd)
			return (ft_lstclear(infos, free), print_error(ERR_MALLOC), false);
		*pfd = fd;
		ft_lstadd_back(infos, ft_lstnew(pfd));
		details = details->next;
	}
	return (true);
}

static bool	iter_redirect_output(t_list *details, t_list **infos)
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
		if (fd < 0)
			return (ft_lstclear(infos, free), false);
		pfd = (int *)malloc(sizeof(int));
		if (!pfd)
			return (ft_lstclear(infos, free), print_error(ERR_MALLOC), false);
		*pfd = fd;
		ft_lstadd_back(infos, ft_lstnew(pfd));
		details = details->next;
	}
	return (true);
}

static void	free_redirect(void *content)
{
	if (*(int *)content != -1)
		close((*(int *)content));
	free(content);
}

bool	init_redirect_files(t_cmd_args *cargs, t_exec_info *info)
{
	t_red_info	red_info;

	red_info = convert_red_info(cargs->redirect);
	if (iter_redirect_input(red_info.red_in, &info->redirect.red_in)
		== false)
		return (false);
	if (iter_redirect_output(red_info.red_out, &info->redirect.red_out)
		== false)
		return (ft_lstclear(&info->redirect.red_in, free_redirect), false);
	return (true);
}
