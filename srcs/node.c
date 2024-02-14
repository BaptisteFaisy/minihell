/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:43:01 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/14 16:12:57 by bfaisy           ###   ########.fr       */
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
	head->redirect.red_out = NULL;
	head->args = NULL;
	head->cmd = NULL;
	head->envp = ev;
	head->next = NULL;
	return (head);
}

void	freeheadcmd(t_cmd_args *head)
{
	t_cmd_args	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		freered(tmp->redirect);
		free(tmp->cmd);
		freelist(tmp->args);
		free(tmp);
	}
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
	t_list	*tmp;

	tmp = *head;
	tmp = get_last(tmp);
	(tmp)->next = malloc(sizeof(t_list));
	if (!(tmp)->next)
		return (-1);
	(tmp)->next->content = data;
	// printf("%sa\n", data);
	return (0);
}

t_list	*get_last(t_list *head)
{
	while (head->next)
		head = head->next;
	return (head);
}
