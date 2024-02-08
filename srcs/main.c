/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:45:12 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/08 17:04:41 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char *test;
	(void)ac ;(void)av; (void)ev;
	while (1)
	{
		write(1, "$> ", 3);
		test = get_next_line(0);
		printf("%s", test);
		if (ft_strncmp(test,"exit",4) == 0)
		{
			free(test);
			return(0);
		}
		free(test);

	}
	return (0);
}
