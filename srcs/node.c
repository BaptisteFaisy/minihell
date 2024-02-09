/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:43:01 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/08 21:03:34 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_list	*get_last(t_list *head);

t_cmd_args	*create_node_cmd(t_cmd_args *head)
{
	head = malloc(sizeof(t_cmd_args));
	if (!head)
	{
		perror("Malloc fail");
		exit (1);
	}
	return (head);
}

int	create_firstnode_and_put(t_list *head, char *data)
{
	head = malloc(sizeof(t_list));
	if (!head)
		return (-1);
	head->content = data;
	return (0);
}

int	create_node_and_put(t_list *head, char *data)
{
	head = get_last(head);
	head->next = malloc(sizeof(t_list));
	if (!head->next)
		return (-1);
	head->next->content = data;
	return (0);
}

t_list	*get_last(t_list *head)
{
	while (head->next)
		head = head->next;
	return (head);
}
