/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_str_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:59:33 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/10 21:40:27 by bfaisy           ###   ########.fr       */
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
	char			*newstr;

	(void)tmp;
	i = 0;
	storage->deja_malloc_boucle = false;
	newstr = str;
	while (str[i])
	{
		storage->cond3 = 0;
		if (str[i] == '$')
		{
			i++;
			if (str[i] == ' ' || str[i] == '\0' || str[i] == ':')
				continue ;
			if (ft_isalpha(str[i]) == 0 && (str[i] != '"' || str[i] != '\'')
				&& str[i] != '?')
			{
				str = rm_is_not_digit(newstr, storage, str);
				// i++;
				storage->cond_is_alpha_dollar = true;
				// printf("%d\n", i);
				continue ;
			}
			// printf("%c\n", str[i]);
			tmp = ev;
			stock = data_after2(str, i);
			// printf("%s\n", stock.str);
			storage->i = i;
			str = transform_str_env2(str, ev, storage, stock);
			if (storage->cond3 == 0)
				str = rmstr(stock, str, storage);
			free(stock.str);
			storage->cond_env = 1;
			i -= 2;
			// printf("%d\n", i);
		}
		i++;
		// printf("%d\n", i);
	}
	// printf("%s\n", str);
	return (str);
}

char	*rmstr(t_string_and_i	stock, char *str, t_storage *storage)
{
	char	*newstr;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	newstr = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!newstr)
		exit (1);
	// printf("%s  %s\n", str, stock.str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] == stock.str[j])
			{
				i++;
				j++;
				if (str[i] == '\0')
				{
					newstr[k] = '\0';
					storage->cond2 = true;
					return (newstr);
				}
				// printf("%c \n", str[i]);
			}
			// printf("%c \n", str[i]);
		}
		newstr[k] = str[i];
		i++;
		k++;
	}
	newstr[k] = '\0';
	storage->cond2 = true;
	if (storage->deja_malloc_boucle == true)
	{
		free(str);
		storage->deja_malloc_boucle = false;
	}
	storage->deja_malloc_boucle = true;
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

char	*replacestr(char *strev, char *str, int cond, t_storage *storage)
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
	if (storage->deja_malloc_boucle == true)
	{
		free(str);
		storage->deja_malloc_boucle = false;
	}
	return (newstr);
}
