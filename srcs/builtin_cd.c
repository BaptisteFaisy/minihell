/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:42:44 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/16 17:07:34 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *err, char *name)
{
	char	*s;

	if (name == NULL)
		s = ft_strjoin_many(4, SHELL_NAME, ": ", "cd: ", err);
	else
		s = ft_strjoin_many(6, SHELL_NAME, ": ", "cd: ", name, ": ", err);
	perror(s);
	free(s);
}

void	builtin_cd(t_cmd_args *cargs, t_exec_info *info)
{
	char	*path;

	if (ft_lstsize(cargs->args) > 2)
	{
		print_error(ERR_CD_TOO_MANY_ARGS, NULL);
		exit(1);
	}
	path = cargs->args->content;
	if (chdir(path) == -1)
	{
		print_error(strerror(errno), path);
		exit(EXEC_FAILURE);
	}
	exit(EXEC_SUCCESS);
}
