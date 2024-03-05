/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:45:12 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/05 18:58:04 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

int	main(int ac, char **av, char **ev)
{
	char	*str;
	t_list	*envp;

	envp = get_list_envp(ev);
	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	while (true)
	{
		str = readline("$> ");
		if (!str)
			return (EXIT_FAILURE);
		if (str && *str)
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
