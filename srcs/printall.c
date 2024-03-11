/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:00:18 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/11 15:03:05 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printall(t_cmd_args *head)
{
	while (head)
	{
		while (head->args)
		{
			printf("args %s\n", (char *) head->args->content);
			head->args = head->args->next;
		}
		printf("cmd %s\n", head->cmd);
		head = head->next;
	}
}