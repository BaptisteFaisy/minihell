/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_after.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:38:41 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/08 21:08:32 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

char	*data_after(char *str, int i)
{
	char	*data;
	int		cond;
	char	*ptr;

	cond = FALSE;
	ptr = NULL;
	while (str[i] == ' ')
			i++;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
			{
				if (cond == TRUE)
					return (data);
				else
					return (((void *)0));
			}
			else
			{
				return ((void *)-1);
			}
		}
		else
		{
			cond = TRUE;
			*ptr = str[i];
			data = ft_strjoin(data, ptr);
			if (!data)
				exit(1);
		}
	}
	return (data);
}

int	find_next_pipe(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (j + 2);
		j++;
		i++;
	}
	return (-1);
}
