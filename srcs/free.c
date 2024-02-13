/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:29:44 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/12 13:39:49 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

void	freelist(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}
