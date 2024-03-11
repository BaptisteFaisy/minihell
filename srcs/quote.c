/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:03:50 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/11 17:36:28 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fuck_les_quotes(char *str)
{
	int		i;
	char	*newstr;
	int		j;

	i = 0;
	j = 0;
	newstr = malloc(sizeof(char) * ft_strlen(str));
	if (!newstr)
		exit (1);
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '"' && str[i + 1] == '"'))
		{
			i += 2;
			continue ;
		}
		newstr[j] = str[i];
		i++;
		j++;
	}
	// free(str);
	return (newstr);
}
