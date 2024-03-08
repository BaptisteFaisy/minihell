/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:54:10 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/09 00:08:32 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_is_not_digit(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = ft_calloc(sizeof(char), ft_strlen(str));
	if (!newstr)
		exit (1);
	while (str[i])
	{
		if (str[i] == '$')
			i += 2;
		newstr[j] = str[i];
		i++;
		j++;
	}
	return (newstr);
}
