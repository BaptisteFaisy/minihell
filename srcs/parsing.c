/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:22:18 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/17 02:09:12 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	parsing(char *str, char **ev)
{
	int				i;
	t_cmd_args		*head;
	int				return_value;
	t_string_and_i	storage;
	t_red			*tmp;

	i = 0;
	head = NULL;
	str = transform_str(str);
	head = create_node_cmd(head, ev);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		// printf("%c\n", str[i]);
		if (str[i] == '<' || str[i] == '>')
		{
			if (head->redirect == NULL)
			{
				create_redirect_node_head(head->redirect);
				tmp = head->redirect;
			}
			else
			{
				tmp = get_last_redirect_node(head->redirect);
				create_redirect_node(tmp);
			}
			return_value = redirect(str, i, tmp);
			// printf("%d\n", return_value);
			if (return_value == -1)
			{
				perror("help");
				return (0);
			}
			if (return_value == 0)
			{
				break ;
			}
			i = return_value;
		}
		else if (head->cmd == NULL && str[i])
		{
			storage = data_after(str, i);
			head->cmd = storage.str;
			i = storage.i;
		}
		else if (str[i])
		{
			storage = data_after(str, i);
			if (!head->args)
				create_firstnode_and_put(&head->args, storage.str);
			else
				create_node_and_put(&head->args, storage.str);
			i = storage.i;
		}
	}
	// printf("cmd : %s\n", head->cmd);
	// while (head->args)
	// {
	// 	printf("args : %s\n", (char *) head->args->content);
	// 	head->args = head->args->next;
	// }
	// while (head->redirect.red_in)
	// {
	// 	printf("redirect.red_in : %s\n", (char*)head->redirect.red_in->content);
	// 	head->redirect.red_in = head->redirect.red_in->next;
	// }
	// while (head->redirect.red_out)
	// {
	// 	printf("redirect.red_out : %s\n", (char *)head->redirect.red_out->content);
	// 	head->redirect.red_out = head->redirect.red_out->next;
	// }
	free(str);
	freeheadcmd(head);
	return (1);
}
