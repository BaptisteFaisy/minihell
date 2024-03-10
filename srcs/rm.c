/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:54:10 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/10 21:36:20 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_is_not_digit(char *oldstr, t_storage *storage, char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = ft_calloc(sizeof(char), ft_strlen(oldstr) + 1);
	if (!newstr)
		exit (1);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 2] != '$' && str[i + 2] != ' '
			&& str[i + 2] != '\0')
			i += 2;
		newstr[j] = str[i];
		i++;
		j++;
	}
	if (storage->deja_malloc_boucle == true)
	{
		free(str);
		storage->deja_malloc_boucle = false;
	}
	return (newstr);
}
