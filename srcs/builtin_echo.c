/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:23:37 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/07 18:09:13 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_option_n(char *s)
{
	int	i;

	if (s[0] == '-' && s[1] == 'n')
	{
		i = 2;
		while (s[i] && s[i] == 'n')
			i++;
		if (s[i] == '\0')
			return (true);
		else
			return (false);
	}
	return (false);
}

int	builtin_echo(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*args;
	bool	n_flag;

	(void)info;
	args = cargs->args;
	n_flag = false;
	while (args && is_option_n((char *)args->content) == true)
	{
		n_flag = true;
		args = args->next;
	}
	while (args)
	{
		ft_putstr_fd((char *)args->content, info->out_fd);
		if (args->next)
			ft_putchar_fd(' ', info->out_fd);
		args = args->next;
	}
	if (n_flag == false)
		ft_putchar_fd('\n', info->out_fd);
	return (EXEC_SUCCESS);
}
