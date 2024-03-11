/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:46:48 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/11 17:34:47 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler_process(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	g_status = 130;
}

void	sigquit_handler_process(int sig)
{
	printf("Quit: %d\n", sig);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	g_status = 130;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
