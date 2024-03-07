/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:01:07 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/07 17:42:05 by lhojoon          ###   ########.fr       */
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

static int	handle_null_behavior(int exit_code, t_cmd_args *cargs)
{
	*cargs->exit_code = -1;
	if (exit_code == 0)
		return (g_status);
	else
		return (exit_code);
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
	if (cargs->head->next != NULL)
		return (handle_null_behavior(exit_code, cargs));
	*cargs->exit_code = exit_code;
	return (EXEC_SUCCESS);
}
