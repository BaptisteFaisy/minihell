/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:59:19 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 21:00:49 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline_str(char *prompt)
{
	char	*str;

	if (isatty(STDIN_FILENO))
		str = readline(prompt);
	else
	{
		ft_putstr_fd(prompt, STDOUT_FILENO);
		str = get_next_line(STDIN_FILENO);
	}
	return (str);
}
