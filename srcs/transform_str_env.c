/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_str_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:59:33 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/06 18:39:20 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*rmstr(t_string_and_i	stock, char *str);
int			compare(char *strev, char *str2, int i);
static char	*replacestr(char *strev, char *str, int cond);

char	*transform_str_env(char *str, t_list *ev, t_cmd_args *head, bool *cond2, bool *cond3)
{
	int				i;
	t_list			*tmp;
	t_string_and_i	stock;
	int				cond;

	i = 0;
	while (str[i])
	{
		cond = 0;
		if (str[i] == '$')
		{
			i++;
			tmp = ev;
			stock = data_after2(str, i, head, cond2);
			while (tmp)
			{
				if (stock.str[0] == '?')
				{
					str = replacestr((char *)tmp->content, str, 1);
					*cond3 = true;
					cond = 1;
					break ;
				}
				if (compare((char *)tmp->content, stock.str, i) == 1)
				{
					str = replacestr((char *)tmp->content, str, 0);
					cond = 1;
					*cond3 = true;
					break ;
				}
				tmp = tmp->next;
			}
			free(stock.str);
			if (cond == 0)
				str = rmstr(stock, str);
		}
		i++;
	}
	return (str);
}

char	*rmstr(t_string_and_i	stock, char *str)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!newstr)
		exit (1);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] == stock.str[i])
				i++;
		}
		newstr[i] = str[i];
		i++;
	}
	newstr[i + 1] = '\0';
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

static char	*replacestr(char *strev, char *str, int cond)
{
	int		i;
	int		j;
	char	*newstr;
	int		k;
	char	*tmp;

	j = 0;
	i = 0;
	k = 0;
	newstr = (char *)ft_calloc(sizeof(char),
			ft_strlen(strev) + ft_strlen(str) + 1);
	if (!newstr)
		exit (1);
	while (str[i] != '$')
	{
		newstr[k] = str[i];
		i++;
		k++;
	}
	i++;
	if (cond == 0)
	{
		while (str[i] == strev[j])
		{
			i++;
			j++;
		}
		j++;
		while (strev[j])
		{
			newstr[k] = strev[j];
			j++;
			k++;
		}
	}
	else
	{
		j = 0;
		tmp = ft_itoa(g_status);
		while ((size_t)j != ft_strlen(tmp))
		{
			newstr[k] = tmp[j];
			j++;
			k++;
		}
		i++;
		free(tmp);
	}
	while (str[i])
	{
		newstr[k] = str[i];
		k++;
		i++;
	}
	newstr[k] = '\0';
	return (newstr);
}
