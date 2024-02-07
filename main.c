/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:45:12 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/07 14:45:38 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	main(int argc, char **argv, char **envp)
{
	signal_handler();
	while (!SIGQUIT && cmd != NULL)
	{
		char	*line = readline();

		if (line == NULL || !strcmp(line, "exit"))
			exit;
		if (lexer(line))
		{
			t_data *data = parser(line, envp);
			execution(data, envp);
		}
	}
	return (0);
}