/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:22:18 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/08 21:09:59 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	parsing(char *str, char **ev)
{
	int			i;
	t_cmd_args	*head;
	int			return_value;

	i = 0;
	(void)ev;
	head = NULL;
	head = create_node_cmd(head);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '<' || str[i] == '>')
		{
			return_value = redirect(str, i, (*head).redirect);
			if (return_value == -1)
			{
				perror("help");
				return (0);
			}
			i += return_value;
		}
		else
		{
			i++;
		}
	}
	return (1);
}
