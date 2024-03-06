/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_red_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:18:31 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/05 21:44:51 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_red_info(t_red_info *info)
{
	info->red_in = NULL;
	info->red_out = NULL;
}

static t_red_details	*new_red_details(char *file, int type)
{
	t_red_details	*details;

	details = (t_red_details *)malloc(sizeof(t_red_details));
	if (!details)
		return (NULL);
	details->file = file;
	details->type = type;
	return (details);
}

t_red_info	convert_red_info(t_red *raw)
{
	t_red_info	info;

	init_red_info(&info);
	while (raw)
	{
		if (raw->red_in)
			ft_lstadd_back(&info.red_in,
				ft_lstnew(new_red_details(raw->red_in, RED_IN)));
		else if (raw->red_out)
			ft_lstadd_back(&info.red_out,
				ft_lstnew(new_red_details(raw->red_out, RED_OUT)));
		else if (raw->red_in_delim)
			ft_lstadd_back(&info.red_in,
				ft_lstnew(new_red_details(raw->red_in_delim, RED_IN_DELIM)));
		else if (raw->red_out_delim)
			ft_lstadd_back(&info.red_out,
				ft_lstnew(new_red_details(raw->red_out_delim, RED_OUT_APPEND)));
		raw = raw->next;
	}
	return (info);
}
