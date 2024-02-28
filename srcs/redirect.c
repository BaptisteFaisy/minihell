/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:37:30 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/28 17:41:17 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static	int	redirect_droite(char *str, int i, t_red *redirect,
				t_cmd_args *head);
static	int	test_error_newline(char *str, int i);
static	int	double_gauche(char *str, int i, t_red *redirect, t_cmd_args *head);
static	int	double_droite(char *str, int i, t_red *redirect, t_cmd_args *head);

int	redirect(char *str, int i, t_red *redirect, t_cmd_args *head)
{
	t_string_and_i	storage;

	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (double_gauche(str, i, redirect, head));
		if (test_error_newline(str, i) == 1)
			return (-1);
		else
		{
			storage = data_after(str, i, head);
			i = storage.i;
			redirect->red_in = storage.str;
			if (storage.i == -100)
				return (-1);
			if (storage.str == NULL)
				return (ft_putstr_fd
					("bash: syntax error near\nunexpected token `newline'\n", 2)
					, g_status = 2, -1);
			return (i);
		}
	}
	else
		return (redirect_droite(str, i, redirect, head));
	return (0);
}

static	int	redirect_droite(char *str, int i, t_red *redirect, t_cmd_args *head)
{
	t_string_and_i	storage;

	if (str[i + 1] == '>')
		return (double_droite(str, i, redirect, head));
	if (test_error_newline(str, i) == 1)
	{
		return (-1);
	}
	else
	{
		storage = data_after(str, i, head);
		i = storage.i;
		redirect->red_out = storage.str;
		if (storage.i == -100)
			return (-1);
		if (storage.str == NULL)
		{
			g_status = 2;
			ft_putstr_fd("bash: syntax error near\nunexpected token `newline'\n",
				2);
			return (-1);
		}
		return (i);
	}
	return (0);
}

static	int	test_error_newline(char *str, int i)
{
	i += 2;
	while (str[i] == ' ')
		i++;
	if (str[i] == '>')
	{
		g_status = 2;
		ft_putstr_fd("bash: syntax error near\nunexpected token '>'\n", 2);
		return (1);
	}
	if (str[i] == '<')
	{
		ft_putstr_fd("bash: syntax error near\nunexpected token '<'\n", 2);
		return (1);
	}
	return (0);
}

static	int	double_gauche(char *str, int i, t_red *redirect, t_cmd_args *head)
{
	t_string_and_i	storage;

	if (test_error_newline(str, i) == 1)
	{
		return (-1);
	}
	storage = data_after(str, i, head);
	i = storage.i;
	redirect->red_in_delim = storage.str;
	if (storage.i == -100)
		return (-1);
	if (storage.str == NULL)
	{
		g_status = 2;
		ft_putstr_fd("bash: syntax error near\nunexpected token `newline'\n", 2);
		return (-1);
	}
	return (i);
}

static	int	double_droite(char *str, int i, t_red *redirect, t_cmd_args *head)
{
	t_string_and_i	storage;

	if (test_error_newline(str, i) == 1)
	{
		return (-1);
	}
	storage = data_after(str, i, head);
	i = storage.i;
	redirect->red_out_delim = storage.str;
	if (storage.i == -100)
		return (-1);
	if (storage.str == NULL)
	{
		g_status = 2;
		ft_putstr_fd("bash: syntax error near\nunexpected token `newline'\n", 2);
		return (-1);
	}
	return (i);
}
