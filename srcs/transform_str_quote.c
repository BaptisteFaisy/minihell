/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_str_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:54:17 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/06 18:35:16 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*transform_str_quote(char *str, bool cond2)
{
	char	*newstr;
	int		i;
	bool	cond_simple;
	bool	cond_double;
	int		j;

	i = 0;
	j = 0;
	cond_simple = false;
	cond_double = false;
	newstr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!newstr)
		exit (1);
	while (str[i])
	{
		if (str[i] == '\'' && cond_simple != true)
		{
			cond_simple = true;
			continue ;
		}
		else if (str[i] == '\'' && cond_simple == true)
		{
			i++;
			while (str[i] != '\'')
			{
				if (str[i] == '\0')
					exit (1);
				newstr[j] = str[i];
				i++;
				j++;
			}
			cond_simple = false;
		}
		else if (str[i] == '"' && cond_double != true)
		{
			cond_double = true;
			continue ;
		}
		else if (str[i] == '"' && cond_double == true)
		{
			i++;
			while (str[i] != '"')
			{
				if (str[i] == '\0')
					exit (1);
				newstr[j] = str[i];
				j++;
				i++;
			}
			cond_double = false;
		}
		else
		{
			newstr[j] = str[i];
			j++;
		}
		i++;
	}
	newstr[j] = '\0';
	if (cond2 == true)
		free(str);
	return (newstr);
}
