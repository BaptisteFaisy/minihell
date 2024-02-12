/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:30:42 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/12 17:14:37 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iter_exec(t_cmd_args *cargs, t_exec_info info)
{
	if (cargs->next)
		pipe(info.tube);
	// TODO
	return (0);
}
