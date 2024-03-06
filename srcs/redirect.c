/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:37:30 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/06 16:46:30 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static	int	redirect_droite(char *str, int i, t_red *redirect,
				t_cmd_args *head, bool *cond);
static	int	test_error_newline(char *str, int i, bool *cond);
static	int	double_gauche(char *str, int i, t_red *redirect, t_cmd_args *head, bool *cond);
static	int	double_droite(char *str, int i, t_red *redirect, t_cmd_args *head, bool *cond);

int	redirect(char *str, int i, t_red *redirect, t_cmd_args *head, bool *cond)
{
	t_string_and_i	storage;

	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (double_gauche(str, i, redirect, head, cond));
		if (test_error_newline(str, i, cond) == 1)
			return (-1);
		else
		{
			storage = data_after(str, i, head, cond);
			i = storage.i;
			redirect->red_in = storage.str;
			if (storage.i == -100)
				return (-1);
			if (storage.str == NULL)
				return (ft_putstr_fd
					("bash: syntax error near\nunexpected token `newline'\n", 2)
					, g_status = 2, *cond = false, -1);
			return (g_status = 0, i);
		}
	}
	else
		return (redirect_droite(str, i, redirect, head, cond));
	return (0);
}

static	int	redirect_droite(char *str, int i, t_red *redirect, t_cmd_args *head, bool *cond)
{
	t_string_and_i	storage;

	if (str[i + 1] == '>')
		return (double_droite(str, i, redirect, head, cond));
	if (test_error_newline(str, i, cond) == 1)
	{
		return (-1);
	}
	else
	{
		storage = data_after(str, i, head, cond);
		i = storage.i;
		redirect->red_out = storage.str;
		if (storage.i == -100)
			return (-1);
		if (storage.str == NULL)
		{
			g_status = 2;
			*cond = false;
			ft_putstr_fd("bash: syntax error near\nunexpected token `newline'\n",
				2);
			return (-1);
		}
		return (g_status = 0, i);
	}
	return (0);
}

static	int	test_error_newline(char *str, int i, bool *cond)
{
	i += 2;
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

static	int	double_gauche(char *str, int i, t_red *redirect, t_cmd_args *head, bool *cond)
{
	t_string_and_i	storage;

	if (test_error_newline(str, i, cond) == 1)
	{
		return (-1);
	}
	storage = data_after(str, i, head, cond);
	i = storage.i;
	redirect->red_in_delim = storage.str;
	if (storage.i == -100)
		return (-1);
	if (storage.str == NULL)
	{
		g_status = 2;
		*cond = false;
		ft_putstr_fd("bash: syntax error near\nunexpected token `newline'\n", 2);
		return (-1);
	}
	return (g_status = 0, i);
}

static	int	double_droite(char *str, int i, t_red *redirect, t_cmd_args *head, bool *cond)
{
	t_string_and_i	storage;

	if (test_error_newline(str, i, cond) == 1)
	{
		return (-1);
	}
	storage = data_after(str, i, head, cond);
	i = storage.i;
	redirect->red_out_delim = storage.str;
	if (storage.i == -100)
		return (-1);
	if (storage.str == NULL)
	{
		g_status = 2;
		*cond = false;
		ft_putstr_fd("bash: syntax error near\nunexpected token `newline'\n", 2);
		return (-1);
	}
	return (g_status = 0, i);
}
