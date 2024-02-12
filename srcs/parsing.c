/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:22:18 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/09 20:39:44 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	parsing(char *str, char **ev)
{
	int			i;
	t_cmd_args	*head;
	int			return_value;

	i = 0;
	head = NULL;
	str = transform_str(str);
	head = create_node_cmd(head, ev);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '<' || str[i] == '>')
		{
			return_value = redirect(str, i, head->redirect);
			if (return_value == -1)
			{
				perror("help");
				return (0);
			}
			if (return_value == 0)
				break ;
			i += return_value;
		}
		else
		{
			i++;
		}
	}
	free(head);
	free(str);
	return (1);
}
