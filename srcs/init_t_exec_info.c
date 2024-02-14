/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_exec_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:42:21 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/14 16:04:52 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_t_exec_info(t_exec_info *var)
{
	var->redirect.red_in = NULL;
	var->redirect.red_out = NULL;
	var->paths = NULL;
}
