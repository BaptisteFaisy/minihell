/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:37:30 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/07 14:34:55 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static	int	redirect_droite(int i, t_red *redirect,
				t_cmd_args *head, t_storage *storage);
static	int	test_error_newline(char *str, int i, bool *cond, int cond2);
static	int	double_gauche(int i, t_red *redirect,
				t_cmd_args *head, t_storage *storage);
static	int	double_droite(int i, t_red *redirect,
				t_cmd_args *head, t_storage *storage);

int	redirect(int i, t_red *redirect, t_cmd_args *head, t_storage *stock)
{
	t_string_and_i	storage;

	if (stock->str[i] == '<')
	{
		if (stock->str[i + 1] == '<')
			return (double_gauche(i, redirect, head, stock));
		if (test_error_newline(stock->str, i, &stock->cond, 0) == 1)
			return (-1);
		else
		{
			storage = data_after(stock->str, i, head, &stock->cond);
			i = storage.i;
			redirect->red_in = storage.str;
			if (storage.i == -100)
				return (-1);
			if (storage.str == NULL)
				return (ft_putstr_fd
					("bash: syntax error near\nunexpected token `newline'\n", 2)
					, g_status = 2, stock->cond = false, -1);
			return (g_status = 0, i);
		}
	}
	else
		return (redirect_droite(i, redirect, head, stock));
	return (0);
}

static	int	redirect_droite(int i,
		t_red *redirect, t_cmd_args *head, t_storage *stock)
{
	t_string_and_i	storage;

	if (stock->str[i + 1] == '>')
		return (double_droite(i, redirect, head, stock));
	if (test_error_newline(stock->str, i, &stock->cond, 0) == 1)
	{
		return (-1);
	}
	else
	{
		storage = data_after(stock->str, i, head, &stock->cond);
		i = storage.i;
		redirect->red_out = storage.str;
		if (storage.i == -100)
			return (-1);
		if (storage.str == NULL)
			return (g_status = 2, stock->cond = false, ft_putstr_fd
				("bash: syntax error near\nunexpected token `newline'\n", 2), -1);
		return (g_status = 0, i);
	}
	return (0);
}

static	int	test_error_newline(char *str, int i, bool *cond, int cond2)
{
	if (cond2 == 1)
		i += 2;
	else
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '>')
	{
		g_status = 2;
		*cond = false;
		ft_putstr_fd("bash: syntax error near\nunexpected token '>'\n", 2);
		return (1);
	}
	if (str[i] == '<')
	{
		g_status = 2;
		*cond = false;
		ft_putstr_fd("bash: syntax error near\nunexpected token '<'\n", 2);
		return (1);
	}
	return (0);
}

static	int	double_gauche(int i, t_red *redirect,
		t_cmd_args *head, t_storage *stock)
{
	t_string_and_i	storage;

	if (test_error_newline(stock->str, i, &stock->cond, 1) == 1)
	{
		return (-1);
	}
	storage = data_after(stock->str, i, head, &stock->cond);
	i = storage.i;
	redirect->red_in_delim = storage.str;
	if (storage.i == -100)
		return (-1);
	if (storage.str == NULL)
	{
		g_status = 2;
		stock->cond = false;
		ft_putstr_fd("bash: syntax error near\nunexpected token `newline'\n", 2);
		return (-1);
	}
	return (g_status = 0, i);
}

static	int	double_droite(int i, t_red *redirect, t_cmd_args *head,
	t_storage *stock)
{
	t_string_and_i	storage;

	if (test_error_newline(stock->str, i, &stock->cond, 1) == 1)
	{
		return (-1);
	}
	storage = data_after(stock->str, i, head, &stock->cond);
	i = storage.i;
	redirect->red_out_delim = storage.str;
	if (storage.i == -100)
		return (-1);
	if (storage.str == NULL)
	{
		g_status = 2;
		stock->cond = false;
		ft_putstr_fd("bash: syntax error near\nunexpected token `newline'\n", 2);
		return (-1);
	}
	return (g_status = 0, i);
}
