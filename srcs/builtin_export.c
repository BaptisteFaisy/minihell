/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:08:56 by marvin            #+#    #+#             */
/*   Updated: 2024/02/20 01:14:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_grammar(t_list *args)
{
	while (args)
	{
		args = args->next;
	}
}

void	builtin_export(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*args;

	exit(EXIT_SUCCESS);
}
