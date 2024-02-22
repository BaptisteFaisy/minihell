/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:37:30 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/22 10:46:10 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static	int	redirect_droite(char *str, int i, t_red *redirect, t_cmd_args *head);
static	int	test_error_newline(char *str, int i, int cas);
static	int	double_gauche(char *str, int i, t_red *redirect, t_cmd_args *head);
static	int	double_droite(char *str, int i, t_red *redirect, t_cmd_args *head);

int	redirect(char *str, int i, t_red *redirect, t_cmd_args *head)
{
	t_string_and_i	storage;

	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (double_gauche(str, i, redirect, head));
		if (test_error_newline(str, i, 0) == 1)
		{
			return (-1);
		}
		else
		{
			storage = data_after(str, i, head);
			i = storage.i;
			redirect->red_in = storage.str;
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
	if (test_error_newline(str, i, 1) == 1)
	{
		return (-1);
	}
	else
	{
		storage = data_after(str, i, head);
		i = storage.i;
		redirect->red_out =  storage.str;
		return (i);
	}
	return (0);
}

static	int	test_error_newline(char *str, int i, int cas)
{
	i++;
	if (cas == 0 && str[i] == '<')
		i++;
	else if (cas == 0 && str[i] == '>')
	{
		ft_putendl_fd("bash: syntax error near \nunexpected token 'newline'", 2);
		return (1);
	}
	else if (cas == 1 && str[i] == '>')
		i++;
	else if (cas == 1 && str[i] == '<')
	{
		ft_putendl_fd("bash: syntax error near \nunexpected token 'newline'", 2);
		return (1);
	}
	if (str[i] == '\0' || str[i] == '|')
	{
		ft_putendl_fd("bash: syntax error near \nunexpected token 'newline'", 2);
		return (1);
	}
	return (0);
}


static	int	double_gauche(char *str, int i, t_red *redirect, t_cmd_args *head)
{
	t_string_and_i	storage;

	// if (test_error_newline(str, i, 1) == 1)
	// {
	// 	return (-1);
	// }
	// else
	// {
	storage = data_after(str, i, head);
	i = storage.i;
				// printf("%s\n",storage.str);

	redirect->red_in_delim =  storage.str;
	return (i);
	// }
	return (0);
}


static	int	double_droite(char *str, int i, t_red *redirect, t_cmd_args *head)
{
	t_string_and_i	storage;

	// if (test_error_newline(str, i, 1) == 1)
	// {
	// 	return (-1);
	// }
	// else
	// {
		storage = data_after(str, i, head);
		i = storage.i;
		redirect->red_out_delim =  storage.str;
		return (i);
	// }
	return (0);
}