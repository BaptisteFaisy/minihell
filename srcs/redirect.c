/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:37:30 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/17 02:24:58 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static	int	redirect_droite(char *str, int i, t_red *redirect);
static	int	test_error_newline(char *str, int i, int cas);

int	redirect(char *str, int i, t_red *redirect)
{
	t_string_and_i	storage;

	if (str[i] == '<')
	{
		// if (str[i + 1] == '<')
		// 	return (double_gauche(str, i, redirect));
		if (test_error_newline(str, i, 0) == 1)
		{
			return (-1);
		}
		else
		{
			storage = data_after(str, i);
			i = storage.i;
			redirect->red_in = malloc(sizeof(char) * ft_strlen(storage.str) + 1);
			ft_strlcpy(redirect->red_in, storage.str, __INT_MAX__);
			redirect->red_in_delim = NULL;
			redirect->red_out_delim = NULL;
			redirect->red_out = NULL;
			return (i);
		}
	}
	else
		return (redirect_droite(str, i, redirect));
	return (0);
}

// void	freered(t_red *redirect)
// {
// 	t_list	*head;

// 	while (redirect)
// 	{
// 		redirect->red_in 
// 	}
// }

static	int	redirect_droite(char *str, int i, t_red *redirect)
{
	char			*data;
	t_string_and_i	storage;

	if (test_error_newline(str, i, 1) == 1)
	{
		return (-1);
	}
	else
	{
		storage = data_after(str, i);
		i = storage.i;
		data = storage.str;
		redirect->red_out = data;
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
