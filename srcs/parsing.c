/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:17:00 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/27 13:54:38 by lhojoon          ###   ########.fr       */
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
	str = transform_str(str);
	if (!str)
		return (0);
	tmpargs = create_node_cmd(&head, ev);
	while (str[i])
	{
		if (tmpargs->is_pipe == 1)
			tmpargs = create_next_node_head(tmpargs, ev);
		while (str[i] == ' ')
			i++;
		// printf("%c\n", str[i]);
		// printf("%c\n", str[i]);
		if (str[i] == '<' || str[i] == '>')
		{
			create_redirect_node_main(tmpargs);
			tmp = get_last_redirect_node(tmpargs->redirect);
			return_value = redirect(str, i, tmp, tmpargs);
			// printf("redirect_out_delim %s\n", head->redirect->red_out_delim);
			// printf("%d\n", return_value);
			if (return_value == -1)
			{
				perror("help");
				return (0);
			}
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
	free(str);
	freeheadcmd(head);
	return (1);
}
