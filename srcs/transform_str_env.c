/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_str_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:59:33 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/07 20:05:49 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*rmstr(t_string_and_i	stock, char *str, t_storage *storage);
int			compare(char *strev, char *str2, int i);

char	*transform_str_env(char *str, t_list *ev,
	t_storage *storage)
{
	int				i;
	t_list			*tmp;
	t_string_and_i	stock;

	i = 0;
	while (str[i])
	{
		storage->cond3 = 0;
		if (str[i] == '$')
		{
			i++;
			tmp = ev;
			stock = data_after2(str, i);
			storage->i = i;
			str = transform_str_env2(str, ev, storage, stock);
			if (storage->cond3 == 0)
				str = rmstr(stock, str, storage);
			free(stock.str);
		}
		i++;
	}
	return (str);
}

char	*rmstr(t_string_and_i	stock, char *str, t_storage *storage)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!newstr)
		exit (1);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] && stock.str[i] && str[i] == stock.str[i])
				i++;
		}
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	storage->cond2 = true;
	return (newstr);
}

int	compare(char *strev, char *str2, int i)
{
	int	j;

	j = 0;
	while (strev[j] == str2[j])
	{
		j++;
		i++;
		if (strev[j] == '=' && str2[j] == '\0')
			return (1);
	}
	return (0);
}

char	*replacestr(char *strev, char *str, int cond)
{
	char		*newstr;
	t_indice	indi;

	indi.i = 0;
	indi.k = 0;
	newstr = (char *)ft_calloc(sizeof(char),
			ft_strlen(strev) + ft_strlen(str) + 1);
	if (!newstr)
		exit (1);
	while (str[indi.i] != '$')
	{
		newstr[indi.k] = str[indi.i];
		indi.i++;
		indi.k++;
	}
	indi.i++;
	if (cond == 0)
		newstr = replacestr3(str, strev, newstr, &indi);
	else
		newstr = replacestr2(newstr, &indi.k, &indi.i);
	while (str[indi.i])
		newstr = replacestr4(newstr, str, &indi);
	newstr[indi.k] = '\0';
	return (newstr);
}
