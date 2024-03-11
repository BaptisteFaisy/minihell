/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_str_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:54:17 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/11 16:55:28 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*transform_str_quote2(char *str, char *newstr, t_indice stock);
char	*transform_str_quote3(t_indice *stock, char *str, char *newstr);
char	*transform_str_quote4(t_indice *stock, char *str, char *newstr);

char	*transform_str_quote(char *str)
{
	char		*newstr;
	t_indice	stock;

	stock.i = 0;
	stock.k = 0;
	stock.cond_simple = false;
	stock.cond_double = false;
	newstr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!newstr)
		exit (1);
	newstr = transform_str_quote2(str, newstr, stock);
	return (newstr);
}

char	*transform_str_quote2(char *str, char *newstr, t_indice stock)
{
	while (str[stock.i])
	{
		if (str[stock.i] == '\'' && stock.cond_simple != true)
		{
			stock.cond_simple = true;
			continue ;
		}
		else if (str[stock.i] == '\'' && stock.cond_simple == true)
			newstr = transform_str_quote3(&stock, str, newstr);
		else if (str[stock.i] == '"' && stock.cond_double != true)
		{
			stock.cond_double = true;
			continue ;
		}
		else if (str[stock.i] == '"' && stock.cond_double == true)
			newstr = transform_str_quote4(&stock, str, newstr);
		else
		{
			newstr[stock.k] = str[stock.i];
			stock.k++;
		}
		stock.i++;
	}
	newstr[stock.k] = '\0';
	return (newstr);
}

char	*transform_str_quote3(t_indice *stock, char *str, char *newstr)
{
	stock->i++;
	while (str[stock->i] != '\'')
	{
		if (str[stock->i] == '\0')
			exit (1);
		newstr[stock->k] = str[stock->i];
		stock->i++;
		stock->k++;
	}
	stock->cond_simple = false;
	return (newstr);
}

char	*transform_str_quote4(t_indice *stock, char *str, char *newstr)
{
	stock->i++;
	while (str[stock->i] != '"')
	{
		if (str[stock->i] == '\0')
			exit (1);
		newstr[stock->k] = str[stock->i];
		stock->k++;
		stock->i++;
	}
	stock->cond_double = false;
	return (newstr);
}
