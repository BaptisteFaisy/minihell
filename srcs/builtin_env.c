// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   builtin_env.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/02/19 16:33:54 by marvin            #+#    #+#             */
// /*   Updated: 2024/02/19 23:54:06 by marvin           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void	builtin_env(t_cmd_args *cargs, t_exec_info *info)
// {
// 	t_list	*lst;

// 	lst = cargs->envp;
// 	while (lst)
// 	{
// 		ft_putstr_fd((char *)lst->content, STDOUT_FILENO);
// 		lst = lst->next;
// 	}
// 	exit(EXEC_SUCCESS);
// }
