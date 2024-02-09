/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:37:30 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/08 21:09:40 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	redirect(char *str, int i, t_red redirect)
{
	char	*data;
	int		nbr;

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
			data = data_after(str, i);
			if (data == ((void *) -1))
				return (-1);
			else if (redirect.red_out == NULL)
				create_firstnode_and_put(redirect.red_in, data);
			else
				create_node_and_put(redirect.red_in, data);
			nbr = find_next_pipe(str, i);
			return (nbr);
		}
	}
	// else
	// 	return (redirect_droite(str, i, redirect));
	return (0);
}

// static int	double_gauche(char *str, int i, t_red redirect)
// {
	
// }

// static int redirect_droite(char *str, int i, t_red redirect)
// {
	
// }

