/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_str_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:59:33 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/28 13:08:51 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			compare(char *strev, char *str2, int i);
void		freestrboucle(t_storage *storage, char *str);

char	*transform_str_env(char *str, t_list *ev,
	t_storage *storage)
{
	int				i;
	t_str_pack		pack;

	i = 0;
	transform_env_initial(storage, &pack, str);
	while (pack.str[i])
	{
		i = transform_env_skip_i(i, pack, &storage);
		if (pack.str[i] == '$')
		{
			i++;
			if (pack.str[i] == ' ' || pack.str[i] == '\0' || pack.str[i] == ':')
				continue ;
			if (ft_isalpha(pack.str[i]) == 0 && (pack.str[i] != '"'
					|| pack.str[i] != '\'') && pack.str[i] != '?')
			{
				pack.str = rm_is_not_digit(pack.newstr, storage, pack.str);
				continue ;
			}
			i = transform_env_suite(i, &pack, ev, &storage);
			continue ;
		}
		i++;
	}
	return (pack.str);
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
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (rmstr_suite(&i, &j, str, stock) == false)
				return (newstr);
		}
		newstr[k++] = str[i++];
	}
	return (freestrboucle(storage, str), storage->deja_malloc_boucle = true,
		storage->cond2 = true, newstr[k] = '\0', newstr);
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
	freestrboucle(storage, str);
	return (free_replace_str(str, storage), newstr);
}

void	freestrboucle(t_storage *storage, char *str)
{
	if (storage->deja_malloc_boucle == true)
	{
		free(str);
		storage->deja_malloc_boucle = false;
	}
}
