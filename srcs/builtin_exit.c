/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:01:07 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 21:33:11 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	verify_numeric(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (false);
		str++;
	}
	return (true);
}

int	builtin_exit(t_cmd_args *cargs, t_exec_info *info)
{
	int		lstsize;
	int		exit_code;

	lstsize = ft_lstsize(cargs->args);
	(void)info;
	if (lstsize > 1)
		return (basherr("exit", ERR_TOO_MANY_ARGS), EXEC_FAILURE);
	if (lstsize == 1)
	{
		if (verify_numeric((char *)cargs->args->content) == false)
		{
			basherr("exit", ERR_NUMERIC_REQUIRED);
			exit_code = EXEC_INVLD_USAGE;
		}
		else
			exit_code = ft_atoi(cargs->args->content);
	}
	else
		exit_code = 0;
	exit(exit_code);
}
