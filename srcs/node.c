/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:43:01 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/09 20:57:00 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_list	*get_last(t_list *head);

t_cmd_args	*create_node_cmd(t_cmd_args *head, char **ev)
{
	head = malloc(sizeof(t_cmd_args));
	if (!head)
	{
		perror("Malloc fail");
		exit (1);
	}
	head->redirect.red_in = NULL;
	head->redirect.red_in_delim = NULL;
	head->redirect.red_out = NULL;
	head->redirect.red_out_append = NULL;
	head->args = NULL;
	head->cmd = NULL;
	head->envp = ev;
	head->next = NULL;
	head->opts = NULL;
	return (head);
}

void	create_firstnode_and_put(t_list **head, char *data)
{
	(*head) = malloc(sizeof(t_list));
	if (!(*head))
		exit (1);
	(*head)->content = data;
}

int	create_node_and_put(t_list **head, char *data)
{
	(*head) = get_last(*head);
	(*head)->next = malloc(sizeof(t_list));
	if (!(*head)->next)
		return (-1);
	(*head)->next->content = data;
	return (0);
}

t_list	*get_last(t_list *head)
{
	while (head->next)
		head = head->next;
	return (head);
}
