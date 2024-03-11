/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:53:57 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/11 16:48:34 by lhojoon          ###   ########.fr       */
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
	int				exit_code;

	parsing_init(&head, &storage);
	exit_code = -1;
	if (check_test(str, &storage.cond) == 1)
		return (0);
	storage.str = transform_str_env(str, ev,
			&storage);
	tmpargs = create_node_cmd(&head, ev);
	head = parsingv2(tmpargs, head, ev, &storage);
	if (storage.cond == true)
	{
		g_status = execution(head);
		exit_code = *head->exit_code;
	}
	if (storage.cond_env == 1)
		free(storage.str);
	freeheadcmd(head);
	if (exit_code != -1)
		return ((exit_code << 2) + 3);
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
		// printf("%c       %d\n", storage->str[i], i);
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
	if (storage->cond_is_alpha_dollar == true)
	{
		storage->cond_is_alpha_dollar = false;
		free(storage->str);
	}
	return (head);
}

int	parsingv3(t_storage *stock, int i, t_cmd_args *tmpargs)
{
	t_string_and_i	storage;

	// printf("da\n");
	storage = data_after(stock, i, tmpargs);
	// printf("%d\n", storage.i);
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
	// printf("%da\n", storage.i);
	(*tmpargs)->cmd = storage.str;
	return (storage.i);
}

t_cmd_args	*create_next_node_head(t_cmd_args *head, t_list *ev)
{
	t_cmd_args	*tmp;

	tmp = malloc(sizeof(t_cmd_args));
	if (!tmp)
		return (basherr(NULL, ERR_MALLOC), exit(EXEC_FAILURE), NULL);
	tmp->redirect = malloc(sizeof(t_red));
	if (!tmp->redirect)
		return (free(tmp), exit(1), NULL);
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
	tmp->exit_code = head->exit_code;
	tmp->head = head;
	return (tmp);
}
