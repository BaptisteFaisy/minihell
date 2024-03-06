/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:53:57 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/06 02:05:55 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_cmd_args	*parsingv2(t_cmd_args *tmpargs, t_cmd_args *head,
				char *str, t_list *ev);
int			parsingv3(char *str, int i, t_cmd_args *tmpargs);
int			parsingv4(char *str, int i, t_cmd_args **tmpargs);

int	parsing(char *str, t_list *ev)
{
	t_cmd_args		*head;
	t_cmd_args		*tmpargs;

	head = NULL;
	g_status = 0;
	if (check_test(str) == 1)
		return (0);
	str = transform_str_env(str, ev, head);
	// printf("%s\n", str);
	str = transform_str(str);
	tmpargs = create_node_cmd(&head, ev);
	head = parsingv2(tmpargs, head, str, ev);
	execution(head);
	free(str);
	freeheadcmd(head);
	return (1);
}

t_cmd_args	*parsingv2(t_cmd_args *tmpargs, t_cmd_args *head,
	char *str, t_list *ev)
{
	int				return_value;
	int				i;
	t_red			*tmp;

	i = 0;
	while (str[i])
	{
		if (tmpargs->is_pipe == 1)
			tmpargs = create_next_node_head(tmpargs, ev);
		i = skipspace(str, i);
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
			i = parsingv4(str, i, &tmpargs);
		else if (str[i])
			i = parsingv3(str, i, tmpargs);
	}
	return (head);
}

int	parsingv3(char *str, int i, t_cmd_args *tmpargs)
{
	t_string_and_i	storage;

	storage = data_after(str, i, tmpargs);
	if (!tmpargs->args)
		create_firstnode_and_put(&tmpargs->args, storage.str);
	else
		create_node_and_put(&tmpargs->args, storage.str);
	return (storage.i);
}

int	parsingv4(char *str, int i, t_cmd_args **tmpargs)
{
	t_string_and_i	storage;

	storage = data_after(str, i, *tmpargs);
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
	head->next = tmp;
	tmp->redirect = NULL;
	tmp->is_first = TRUE;
	tmp->args = NULL;
	tmp->cmd = NULL;
	tmp->is_pipe = 0;
	tmp->envp = ev;
	tmp->next = NULL;
	return (tmp);
}
