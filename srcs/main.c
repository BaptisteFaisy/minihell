/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:45:12 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/07 00:15:44 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

int	main(int ac, char **av, char **ev)
{
	char	*str;
	t_list	*envp;

	signals();
	envp = get_list_envp(ev);
	(void)av;
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
		if (parsing(str, envp) == 0)
			continue ;
		if (ft_strncmp(str, "exit", 4) == 0)
		{
			rl_clear_history();
			return (free(str), ft_lstclear(&envp, free), 0);
		}
		free(str);
	}
}
