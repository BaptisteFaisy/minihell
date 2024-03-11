/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:59:43 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/11 16:47:55 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_last(t_list *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	parsing_init(t_cmd_args **head, t_storage *storage)
{
	*head = NULL;
	storage->cond = true;
	storage->cond2 = false;
	storage->cond_env = 0;
	storage->cond_is_alpha_dollar = false;
}
