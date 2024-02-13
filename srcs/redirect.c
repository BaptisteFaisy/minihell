/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:37:30 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/12 15:31:06 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	redirect(char *str, int i, t_red *redirect)
{
	char			*data;
	t_string_and_i	storage;

	if (str[i] == '<')
	{
		// if (str[i + 1] == '<')
		// 	return (double_gauche(str, i, redirect));
		if (str[i + 1] == '>')
		{
			return (-1);
		}
		else
		{
			storage = data_after(str, i);
			i = storage.i;
			data = storage.str;
			if (redirect->red_in == NULL)
				create_firstnode_and_put(&redirect->red_in, data);
			else
				create_node_and_put(&redirect->red_in, data);
			return (i);
		}
	}
	return (0);
}

// static int	double_gauche(char *str, int i, t_red redirect)
// {
	
// }

// static int redirect_droite(char *str, int i, t_red redirect)
// {
	
// }

void	freered(t_red redirect)
{
	t_list	*head;

	while (redirect.red_in)
	{
		head = redirect.red_in;
		redirect.red_in = redirect.red_in->next;
		if (head->content)
			free (head->content);
		free(head);
	}
}
