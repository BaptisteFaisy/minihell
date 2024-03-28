/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_str_env_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:30:36 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/28 13:07:42 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*transform_str_env2(char *str, t_list *ev,
		t_storage *storage, t_string_and_i stock)
{
	t_list	*tmp;

	tmp = ev;
	while (tmp)
	{
		if (stock.str[0] == '?')
		{
			str = replacestr((char *)tmp->content, str, 1, storage);
			storage->cond2 = true;
			storage->cond3 = 1;
			break ;
		}
		if (compare((char *)tmp->content, stock.str, storage->i) == 1)
		{
			str = replacestr((char *)tmp->content, str, 0, storage);
			storage->cond3 = 1;
			storage->cond2 = true;
			break ;
		}
		tmp = tmp->next;
	}
	return (str);
}

char	*replacestr2(char *newstr, int *k, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = ft_itoa(g_status);
	while ((size_t)j != ft_strlen(tmp))
	{
		newstr[*k] = tmp[j];
		j += 1;
		*k += 1;
	}
	*i += 1;
	free(tmp);
	return (newstr);
}

char	*replacestr3(char *str, char *strev, char *newstr, t_indice *indi)
{
	int		j;

	j = 0;
	while (str[indi->i] == strev[j])
	{
		indi->i++;
		j++;
	}
	j++;
	while (strev[j])
	{
		newstr[indi->k] = strev[j];
		j++;
		indi->k++;
	}
	return (newstr);
}

char	*replacestr4(char *newstr, char *str, t_indice *indi)
{
	newstr[indi->k] = str[indi->i];
	indi->k++;
	indi->i++;
	return (newstr);
}

void	free_replace_str(char *str, t_storage *storage)
{
	if (storage->deja_malloc_boucle == true)
	{
		free(str);
		storage->deja_malloc_boucle = false;
	}
	storage->deja_malloc_boucle = true;
}
