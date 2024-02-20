/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:10:06 by marvin            #+#    #+#             */
/*   Updated: 2024/02/19 23:51:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_list_envp(char **envp)
{
	t_list	*list;
	int		i;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (list);
}

char	**transform_envp(t_list *envp)
{
	char	**envp_arr;
	int		i;

	envp_arr = (char **)malloc(sizeof(char *) * (ft_lstsize(envp) + 1));
	if (!envp_arr)
		return (NULL);
	i = 0;
	while (envp)
	{
		envp_arr[i] = (char *)envp->content;
		envp = envp->next;
		i++;
	}
	envp_arr[i] = NULL;
	return (envp_arr);
}
