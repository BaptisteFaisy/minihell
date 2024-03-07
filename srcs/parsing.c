/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:53:57 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/07 19:54:04 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_cmd_args	*parsingv2(t_cmd_args *tmpargs, t_cmd_args *head,
				t_list *ev, t_storage *storage);
int			parsingv3(t_storage *storage, int i, t_cmd_args *tmpargs);
int			parsingv4(t_storage *stock, int i, t_cmd_args **tmpargs);

int	parsing(char *str, t_list *ev)
{
	t_cmd_args		*head;
	t_cmd_args		*tmpargs;
	t_storage		storage;
	bool			cond_space;

	storage.cond = true;
	storage.cond2 = false;
	cond_space = false;
	head = NULL;
	if (check_test(str, &storage.cond) == 1)
		return (0);
	storage.str = transform_str_env(str, ev,
			&storage);
	// storage.str = fuck_les_quotes(storage.str);
	// printf("%s\n", storage.str);
	// storage.str = transform_str(storage.str); // atm c'est de la grosse merde
	// printf("%s\n", storage.str);
	tmpargs = create_node_cmd(&head, ev);
	head = parsingv2(tmpargs, head, ev, &storage);
	// storage.str = transform_str_quote(storage.str, storage.cond2);
	if (storage.cond == true)
		g_status = execution(head);
	// printf("a\n");
	free(storage.str);
	freeheadcmd(head);
	return (1);
}

t_cmd_args	*parsingv2(t_cmd_args *tmpargs, t_cmd_args *head,
	t_list *ev, t_storage *storage)
{
	int				return_value;
	int				i;
	t_red			*tmp;
	// t_string_and_i	bank;

	i = 0;
	while (storage->str[i])
	{
		if (tmpargs->is_pipe == 1)
			tmpargs = create_next_node_head(tmpargs, ev);
		i = skipspace(storage->str, i);
		if (storage->str[i] == '<' || storage->str[i] == '>')
		{
			create_redirect_node_main(tmpargs);
			tmp = get_last_redirect_node(tmpargs->redirect);
			return_value = redirect(i, tmp, tmpargs, storage);
			if (return_value == -1)
				return (0);
			i = return_value;
		}
		else if (tmpargs->cmd == NULL && storage->str[i])
			i = parsingv4(storage, i, &tmpargs);
		else if (storage->str[i])
			i = parsingv3(storage, i, tmpargs);
	}
	return (head);
}

int	parsingv3(t_storage *stock, int i, t_cmd_args *tmpargs)
{
	t_string_and_i	storage;

	storage = data_after(stock, i, tmpargs);
	if (storage.str == NULL)
		return (i +2);
	// printf("%s\n", storage.str);

	if (!tmpargs->args)
		create_firstnode_and_put(&tmpargs->args, storage.str);
	else
		create_node_and_put(&tmpargs->args, storage.str);
	return (storage.i);
}

int	parsingv4(t_storage *stock, int i, t_cmd_args **tmpargs)
{
	t_string_and_i	storage;

	storage = data_after(stock, i, *tmpargs);
	if (storage.str == NULL)
		return (i +2);
	(*tmpargs)->cmd = storage.str;
	return (storage.i);
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
	tmp->redirect = malloc(sizeof(t_red));
	if (!tmp->redirect)
		exit(1);
	head->next = tmp;
	tmp->redirect->red_out = NULL;
	tmp->redirect->red_in = NULL;
	tmp->redirect->red_in_delim = NULL;
	tmp->redirect->red_out_delim = NULL;
	tmp->redirect->next = NULL;
	tmp->is_first = TRUE;
	tmp->args = NULL;
	tmp->cmd = NULL;
	tmp->is_pipe = 0;
	tmp->envp = ev;
	tmp->next = NULL;
	return (tmp);
}
