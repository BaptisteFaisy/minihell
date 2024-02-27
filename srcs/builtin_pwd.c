/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:53:47 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/27 14:13:13 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *error)
{
	char	*s;

	s = ft_strjoin_many(3, SHELL_NAME, ": ", error);
	perror(s);
	free(s);
}

int	builtin_pwd(t_cmd_args *cargs, t_exec_info *info)
{
	char	*pwd;

	(void)cargs;
	(void)info;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_error(ERR_GETCWD);
		return (EXEC_FAILURE);
	}
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	return (EXEC_SUCCESS);
}
