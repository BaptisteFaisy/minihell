/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:33:04 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/13 21:37:28 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler_heredoc(int sig)
{
	char	c;

	c = EOF;
	(void)sig;
	g_status = -1;
	write(0, &c, 1);
}

void	sigquit_handler_heredoc(int sig)
{
	(void)sig;
	g_status = 0;
	printf("Fuck\n");
	basherr(NULL, WARN_HEREDOC_DELIM);
}
