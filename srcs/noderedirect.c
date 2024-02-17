/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noderedirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:56:42 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/17 02:21:34 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

void	create_redirect_node(t_red *head)
{
	t_red	*next;

	next = malloc(sizeof(t_red));
	if (!next)
		exit (1);
	head->next = next;
	next->red_in = NULL;
	next->red_in_delim = NULL;
	next->red_out = NULL;
	next->red_out_delim = NULL;
	next->next = NULL;
}

void create_redirect_node_head(t_red *head)
{
	head = malloc(sizeof(t_red));
	if (!head)
		exit (1);
	// printf("a\n");
	head->next = NULL;
}

t_red	*get_last_redirect_node(t_red *head)
{
	if (!head)
		return (head);
	while (head->next)
		head = head->next;
	return (head);
}