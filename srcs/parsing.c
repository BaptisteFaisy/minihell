/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:53:57 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/27 16:56:13 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	parsing(char *str, t_list *ev)
{
	int				i;
	t_cmd_args		*head;
	int				return_value;
	t_string_and_i	storage;
	t_red			*tmp;
	t_cmd_args		*tmpargs;

	i = 0;
	head = NULL;
	if (check_test(str) == 1)
		return (0);
	str = transform_str(str);
	tmpargs = create_node_cmd(&head, ev);
	while (str[i])
	{
		if (tmpargs->is_pipe == 1)
			tmpargs = create_next_node_head(tmpargs, ev);
		while (str[i] == ' ')
			i++;
		if (str[i] == '<' || str[i] == '>')
		{
			create_redirect_node_main(tmpargs);
			tmp = get_last_redirect_node(tmpargs->redirect);
			return_value = redirect(str, i, tmp, tmpargs);
			if (return_value == -1)
				return (0);
			i = return_value;
		}
		else if (tmpargs->cmd == NULL && str[i])
		{
			storage = data_after(str, i, tmpargs);
			tmpargs->cmd = storage.str;
			i = storage.i;
		}
		else if (str[i])
		{
			storage = data_after(str, i, tmpargs);
			if (!tmpargs->args)
				create_firstnode_and_put(&tmpargs->args, storage.str);
			else
				create_node_and_put(&tmpargs->args, storage.str);
			i = storage.i;
		}
	}
	execution(head);
	free(str);
	freeheadcmd(head);
	return (1);
}

	// while (head)
	// {
	// 	while (head->redirect)
	// 	{
	// 		printf("redirect_in %s\n", head->redirect->red_in);
	// 		head->redirect = head->redirect->next;
	// 	}
	// 	head = head->next;
	// 	// printf("a\n");
	// }
	// printf("cmd : %s\n", head->cmd);
	// while (head->args)
	// {
	// 	printf("args %s \n", (char *)head->args->content);
	// 	head->args = head->args->next;
	// }
	// while (head->redirect)
	// {
	// 	printf("redirect_in %s\n", head->redirect->red_in);
	// 	head->redirect = head->redirect->next;
	// }
	// while (head->redirect)
	// {
	// 	printf("redirect_out %s\n", head->redirect->red_out);
	// 	head->redirect = head->redirect->next;
	// }
	// while (head->redirect)
	// {
	// 	printf("redirect_out_delim %s\n", head->redirect->red_out_delim);
	// 	head->redirect = head->redirect->next;
	// }
	// while (head->redirect)
	// {
	// 	printf("redirect_in_delim %s\n", head->redirect->red_in_delim);
	// 	head->redirect = head->redirect->next;
	// }

t_cmd_args	*create_next_node_head(t_cmd_args *head, t_list *ev)
{
	t_cmd_args	*tmp;

	tmp = malloc(sizeof(t_cmd_args));
	if (!tmp)
	{
		perror("Malloc fail");
		exit (1);
	}
	head->next = tmp;
	tmp->redirect = malloc(sizeof(t_red));
	if (!tmp->redirect)
		exit(1);
	tmp->redirect->red_out = NULL;
	tmp->redirect->red_in = NULL;
	tmp->redirect->red_in_delim = NULL;
	tmp->redirect->red_out_delim = NULL;
	tmp->is_first = TRUE;
	tmp->args = NULL;
	tmp->cmd = NULL;
	tmp->is_pipe = 0;
	tmp->ep = ev;
	tmp->next = NULL;
	return (tmp);
}
