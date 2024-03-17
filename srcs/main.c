/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:45:12 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/17 23:24:09 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_status = 0;

int	main(int ac, char **av, char **ev)
{
	char	*str;
	t_list	*envp;
	int		exit_code;

	(void)av;
	envp = get_list_envp(ev);
	if (ac != 1)
		return (EXIT_FAILURE);
	while (true)
	{
		str = readline_str("$> ");
		if (!str)
			return (ft_putendl_fd("exit", 1),
				ft_lstclear(&envp, free), EXIT_FAILURE);
		if (isatty(STDIN_FILENO) && str && *str)
			add_history(str);
		exit_code = parsing(str, envp);
		if (exit_code == 0)
			continue ;
		if (exit_code != 1)
			return (free(str), ft_lstclear(&envp, free),
				exit(exit_code >> 2), 1);
		free(str);
	}
}
