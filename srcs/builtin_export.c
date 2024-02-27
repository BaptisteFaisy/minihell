/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:08:56 by marvin            #+#    #+#             */
/*   Updated: 2024/02/27 16:59:00 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_string_value(char *str)
{
	char	*retstr;

	if (ft_strchr(str, '=') == 0)
		retstr = ft_strjoin(str, "=");
	else
		retstr = ft_strdup(str);
	return (retstr);
}

static int	get_key_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static void	replace_existing_envp(t_list *args, t_exec_info *info,
	t_list *envp, bool *exist)
{
	(void)info;
	*exist = true;
	free(envp->content);
	envp->content = ft_strdup(args->content);
}

int	builtin_export(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*args;
	t_list	*envp;
	bool	exist;

	args = cargs->args;
	while (args)
	{
		exist = false;
		envp = cargs->envp;
		while (envp)
		{
			if (ft_strncmp((char *)args->content, (char *)envp->content,
					get_key_len((char *)args->content)) == 0)
			{
				replace_existing_envp(args, info, envp, &exist);
				break ;
			}
			envp = envp->next;
		}
		if (!exist)
			ft_lstadd_back(&cargs->envp,
				ft_lstnew(get_string_value((char *)args->content)));
		args = args->next;
	}
	return (EXIT_SUCCESS);
}
