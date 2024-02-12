/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_exec_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:42:21 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/12 10:43:59 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_t_exec_info(t_exec_info *var)
{
	var->redirect.red_in = NULL;
	var->redirect.red_in_delim = NULL;
	var->redirect.red_out = NULL;
	var->redirect.red_out_append = NULL;
	var->paths = NULL;
}
