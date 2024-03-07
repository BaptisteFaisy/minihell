/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:43:01 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/07 17:59:31 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_list	*get_last(t_list *head);

t_cmd_args	*create_node_cmd(t_cmd_args **head, t_list *ev)
{
	(*head) = malloc(sizeof(t_cmd_args));
	if (!(*head))
		return (basherr(NULL, ERR_MALLOC), exit(EXEC_FAILURE), NULL);
	(*head)->redirect = malloc(sizeof(t_red));
	if (!(*head)->redirect)
		return (free(*head), exit(1), NULL);
	(*head)->redirect->red_out = NULL;
	(*head)->redirect->red_in = NULL;
	(*head)->redirect->red_in_delim = NULL;
	(*head)->redirect->red_out_delim = NULL;
	(*head)->redirect->next = NULL;
	(*head)->is_first = TRUE;
	(*head)->args = NULL;
	(*head)->cmd = NULL;
	(*head)->is_pipe = 0;
	(*head)->envp = ev;
	(*head)->next = NULL;
	(*head)->exit_code = malloc(sizeof(int));
	if (!(*head)->exit_code)
		return (free(*head), free((*head)->redirect), exit(1), NULL);
	*((*head)->exit_code) = -1;
	(*head)->head = *head;
	return (*head);
}

static void	free_tmp_freeheadcmd(t_cmd_args *tmp)
{
	freelist(tmp->args);
	free(tmp);
}

void	freeheadcmd(t_cmd_args *head)
{
	t_cmd_args	*tmp;
	t_red		*tmpred;

	free(head->exit_code);
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->cmd);
		while (tmp->redirect)
		{
			tmpred = tmp->redirect;
			tmp->redirect = tmp->redirect->next;
			if (tmpred->red_in)
				free(tmpred->red_in);
			if (tmpred->red_in_delim)
				free(tmpred->red_in_delim);
			if (tmpred->red_out)
				free(tmpred->red_out);
			if (tmpred->red_out_delim)
				free(tmpred->red_out_delim);
			free(tmpred);
		}
		free_tmp_freeheadcmd(tmp);
	}
}

void	create_firstnode_and_put(t_list **head, char *data)
{
	(*head) = malloc(sizeof(t_list));
	if (!(*head))
		exit (1);
	(*head)->content = data;
	(*head)->next = NULL;
}

int	create_node_and_put(t_list **head, char *data)
{
	t_list	*tmp;
	t_list	*t2;

	tmp = *head;
	tmp = get_last(tmp);
	t2 = ft_lstnew(data);
	if (!t2)
		return (-1);
	(tmp)->next = t2;
	return (0);
}

