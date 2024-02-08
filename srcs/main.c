/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:45:12 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/08 17:21:43 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char	*str;
	(void)ac ;(void)av; (void)ev;
	while (1)
	{
		write(1, "$> ", 3);
		str = get_next_line(0);
		parsing(str);
		if (ft_strncmp(str, "exit", 4) == 0)
		{
			free(str);
			return (0);
		}
		free(str);
	}
	return (0);
}
