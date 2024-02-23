/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:47:21 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/23 13:16:41 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_args(char *cmd, t_list *args)
{
	char	**argv;
	int		i;

	argv = (char **)malloc(sizeof(char *) * (ft_lstsize(args) + 2));
	if (!argv)
		return (perror(ERR_MALLOC), NULL);
	argv[0] = cmd;
	i = 1;
	while (args)
	{
		argv[i] = (char *)args->content;
		args = args->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
