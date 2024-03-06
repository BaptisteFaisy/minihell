/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:20:23 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/06 16:46:09 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	check_test(char *str, bool *cond)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == ';')
	{
		g_status = 2;
		*cond = false;
		ft_putstr_fd("bash: syntax error near\nunexpected token `;'\n", 2);
		return (1);
	}
	if (str[i] == '\n')
		return (1);
	else if (str[i] == '|')
	{
		g_status = 2;
		*cond = false;
		ft_putstr_fd("bash: syntax error near\nunexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}
