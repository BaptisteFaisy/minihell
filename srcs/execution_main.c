/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:37:49 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/04 18:10:06 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution(t_cmd_args *cargs)
{
	char	**paths;

	if (cargs->envp == NULL)
		printf("envp is NULL\n");
	paths = resolve_path(cargs->envp);
	if (paths == NULL)
		return (EXEC_FAILURE);
	return (ft_freesplit(paths), iter_exec(cargs, paths));
}
