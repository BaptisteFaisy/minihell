/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:21:19 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/27 16:11:18 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

char	*transform_str(char *str)
{
	char	*new_str;
	int		i;
	int		cond;
	int		j;

	i = 0;
	cond = FALSE;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		exit (1);
	while (str[i])
	{
		if (str[i] == ' ' && cond == FALSE)
		{
			cond = TRUE;
			new_str[j] = str[i];
			j++;
		}
		else if (str[i] != ' ')
		{
			cond = FALSE;
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j - 1] = '\0';
	while (j != (int)ft_strlen(str) + 1)
	{
		new_str[j] = '\0';
		j++;
	}
	return (new_str);
}
