/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noderedirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:56:42 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/06 20:49:58 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

void	create_redirect_node(t_red *head)
{
	t_red	*next1;

	next1 = malloc(sizeof(t_red));
	if (!next1)
		exit (1);
	head->next = next1;
	next1->red_in = NULL;
	next1->red_in_delim = NULL;
	next1->red_out = NULL;
	next1->red_out_delim = NULL;
	next1->next = NULL;
}

void	create_redirect_node_main(t_cmd_args *head)
{
	if (head->is_first == TRUE)
		head->is_first = FALSE;
	else
		create_redirect_node(head->redirect);
}

t_red	*get_last_redirect_node(t_red *head)
{
	while (head->next)
		head = head->next;
	return (head);
}
