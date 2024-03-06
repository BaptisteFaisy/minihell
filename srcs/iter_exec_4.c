/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_exec_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:15:56 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 23:30:16 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	activate_sig_process(t_exec_info *info)
{
	info->oldsint = signal(SIGINT, sigint_handler_process);
	info->oldsquit = signal(SIGQUIT, sigquit_handler_process);
}

void	deactivate_sig_process(t_exec_info *info)
{
	signal(SIGINT, info->oldsint);
	signal(SIGQUIT, info->oldsquit);
}
