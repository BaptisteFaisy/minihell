/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:08:56 by marvin            #+#    #+#             */
/*   Updated: 2024/03/11 17:02:48 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_string_value(char *str)
{
	char	*retstr;
	char	*chrstr;

	chrstr = ft_strchr(str, '=');
	if (chrstr == NULL)
		retstr = ft_strdup(str);
	else if (*(chrstr + 1) == '\0')
		retstr = ft_strjoin_many(2, str, "\"\"");
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

static void	replace_envp(t_list *args, t_exec_info *info,
	t_list *envp, bool *exist)
{
	while (envp)
	{
		if (ft_strncmp((char *)args->content, (char *)envp->content,
				get_key_len((char *)args->content)) == 0)
		{
			replace_existing_envp(args, info, envp, exist);
			break ;
		}
		envp = envp->next;
	}
}

int	builtin_export(t_cmd_args *cargs, t_exec_info *info)
{
	t_list	*args;
	t_list	*envp;
	bool	exist;
	char	*s;

	if (cargs->args == NULL)
		return (print_env_export(cargs, info));
	args = cargs->args;
	while (args)
	{
		if (!is_valid_env_name((char *)args->content))
		{
			s = ft_strjoin_many(3, "export: '", (char *)args->content, "'");
			return (basherr(s, ERR_VALID_IDENTIFIER), free(s),
				EXEC_FAILURE);
		}
		exist = false;
		envp = cargs->envp;
		replace_envp(args, info, envp, &exist);
		if (!exist)
			ft_lstadd_back(&cargs->envp,
				ft_lstnew(get_string_value((char *)args->content)));
		args = args->next;
	}
	return (EXEC_SUCCESS);
}
