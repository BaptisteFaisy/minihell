/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:41:56 by marvin            #+#    #+#             */
/*   Updated: 2024/03/09 09:07:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_print_value(char *str)
{
	char	*sp;
	int		idx;
	bool	is_met;

	sp = (char *)malloc((ft_strlen(str) + 3) * sizeof(char));
	idx = 0;
	is_met = false;
	if (!sp)
		return (NULL);
	while (*str)
	{
		*(sp + idx++) = *str;
		if (is_met == false && *str == '=')
		{
			is_met = true;
			*(sp + idx++) = '"';
		}
		str++;
	}
	if (is_met == true)
		*(sp + idx++) = '"';
	*(sp + idx) = '\0';
	return (sp);
}

int	print_env_export(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*lst;
	char	*s;

	(void)info;
	lst = cargs->envp;
	while (lst)
	{
		s = get_print_value((char *)lst->content);
		if (!s)
			return (EXEC_FAILURE);
		ft_putstr_fd("export ", info->out_fd);
		ft_putendl_fd(s, info->out_fd);
		free(s);
		lst = lst->next;
	}
	return (EXEC_SUCCESS);
}
