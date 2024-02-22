/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:37:45 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/12 19:07:17 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool
	handle_redirect(t_list *in, t_list **out, int access_flag, int open_flag)
{
	if (in == NULL)
		*out = NULL;
	*out = ft_lstnew(redirect_open(in->content, access_flag, open_flag));
	in = in->next;
	while (in)
	{
		ft_lstadd_back(out,
			ft_lstnew(redirect_open(in->content, access_flag, open_flag)));
		in = in->next;
	}
}

int	redirect_handler(t_cmd_args *cargs, t_exec_info *info)
{
	handle_redirect(cargs->redirect.red_in, &info->redirect.red_in, R_OK, O_RDONLY);
	handle_redirect(cargs->redirect.red_out, &info->redirect.red_out);
	handle_redirect(cargs->redirect.red_out_append, &info->redirect.red_out_append);
	return (0);
}
