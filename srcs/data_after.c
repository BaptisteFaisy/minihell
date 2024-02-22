/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_after.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:38:41 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/22 10:48:32 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

char	*concatenation(char *str, char c);

t_string_and_i	data_after(char *str, int i, t_cmd_args *head)
{
	t_string_and_i	data;

	data.str = NULL;
	data.i = i;
	// printf("int avant data_after : %d\n", data.i);
	// printf("str[i] in data after : %d\n", i);
	while (str[data.i] == ' ' || str[data.i] == '<' || str[data.i] == '>')
			data.i++;
	while (str[data.i])
	{
		if (str[data.i] == ' ')
			break ;
		else if (str[data.i] == '|')
		{
			data.i++;
			head->is_pipe = 1;
			break;
		}
		else
		{
			data.str = concatenation(data.str, str[data.i]);
			if (!data.str)
				exit(1);
		}
		data.i++;
	}
	// printf("%c", str[data.i]);
	return (data);
}

int	find_next_pipe(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (j + 1);
		j++;
		i++;
	}
	return (0);
}

char	*concatenation(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	if (str)
	{
		new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
		if (!new_str)
			exit (1);
		ft_strlcpy(new_str, str, ft_strlen(str) + 2);
		while (str[i])
			i++;
		new_str[i] = c;
		new_str[i + 1] = '\0';
		free(str);
	}
	else
	{
		new_str = malloc(sizeof(char) * 2);
		if (!new_str)
			exit(1);
		new_str[0] = c;
		new_str[1] = '\0';
	}
	return (new_str);
}
