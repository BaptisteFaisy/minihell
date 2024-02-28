/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:21:19 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/27 17:16:53 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	transform_str2(char *str, int i, int j, char **new_str);

char	*transform_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		exit (1);
	j = transform_str2(str, i, j, &new_str);
	while (j != (int)ft_strlen(str) + 1)
	{
		new_str[j] = '\0';
		j++;
	}
	return (new_str);
}

int	transform_str2(char *str, int i, int j, char **new_str)
{
	int		cond;

	cond = FALSE;
	while (str[i])
	{
		if (str[i] == ' ' && cond == FALSE)
		{
			cond = TRUE;
			(*new_str)[j] = str[i];
			j++;
		}
		else if (str[i] != ' ')
		{
			cond = FALSE;
			(*new_str)[j] = str[i];
			j++;
		}
		i++;
	}
	(*new_str)[j - 1] = '\0';
	return (j);
}
