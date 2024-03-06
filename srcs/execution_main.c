/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:37:49 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 16:58:24 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution(t_cmd_args *cargs)
{
	char	**paths;
	int		res;

	if (cargs->envp == NULL)
		printf("envp is NULL\n");
	paths = resolve_path(cargs->envp);
	if (paths == NULL)
		return (EXEC_FAILURE);
	res = iter_exec(cargs, paths);
	ft_putstr_fd(ft_itoa(res), 2);
	return (ft_freesplit(paths), res);
}
