/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:53:57 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/07 17:43:14 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_cmd_args	*parsingv2(t_cmd_args *tmpargs, t_cmd_args *head,
				t_list *ev, t_storage *storage);
int			parsingv3(char *str, int i, t_cmd_args *tmpargs, bool *cond);
int			parsingv4(char *str, int i, t_cmd_args **tmpargs, bool *cond);

int	parsing(char *str, t_list *ev)
{
	t_cmd_args		*head;
	t_cmd_args		*tmpargs;
	t_storage		storage;
	int				exit_code;

	storage.cond = true;
	storage.cond2 = false;
	head = NULL;
	if (check_test(str, &storage.cond) == 1)
		return (0);
	storage.str = transform_str_env(str, ev,
			&storage);
	storage.str = transform_str_quote(storage.str, storage.cond2);
	storage.str = transform_str(storage.str);
	tmpargs = create_node_cmd(&head, ev);
	head = parsingv2(tmpargs, head, ev, &storage);
	free(storage.str);
	if (storage.cond == true)
		g_status = execution(head);
	exit_code = *head->exit_code;
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
			i = parsingv4(storage->str, i, &tmpargs, &storage->cond);
		else if (storage->str[i])
			i = parsingv3(storage->str, i, tmpargs, &storage->cond);
	}
	return (head);
}

int	parsingv3(char *str, int i, t_cmd_args *tmpargs, bool *cond)
{
	t_string_and_i	storage;

	storage = data_after(str, i, tmpargs, cond);
	if (!tmpargs->args)
		create_firstnode_and_put(&tmpargs->args, storage.str);
	else
		create_node_and_put(&tmpargs->args, storage.str);
	return (storage.i);
}

int	parsingv4(char *str, int i, t_cmd_args **tmpargs, bool *cond)
{
	t_string_and_i	storage;

	storage = data_after(str, i, *tmpargs, cond);
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
