/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:45:12 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/08 20:54:19 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char	*str;

	(void)av;
	if (ac != 1)
		return (1);
	while (1)
	{
		write(1, "$> ", 3);
		str = get_next_line(0);
		if (parsing(str, ev) == 0)
			continue ;
		if (ft_strncmp(str, "exit", 4) == 0)
		{
			free(str);
			return (0);
		}
		free(str);
	}
	return (0);
}
