/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:27:50 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/16 17:08:00 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *path, char *err)
{
	char	*s;

	if (path == NULL)
		s = ft_strjoin_many(3, SHELL_NAME, ": ", err);
	else
		s = ft_strjoin_many(5, SHELL_NAME, ": ", path, ": ", err);
	if (!s)
	{
		perror(ERR_UNKNOWN);
		return ;
	}
	perror(s);
	free(s);
}

// TODO : Verify all existing errors
static bool	access_file(char *path, int type)
{
	int	access_result;

	access_result = access(path, type & (F_OK | R_OK | W_OK | X_OK));
	if (access_result == 0)
		return (true);
	if (errno == ENOENT && type & F_SKIP_NUL == 0)
		return (true);
	print_error(path, strerror(errno));
	return (false);
}

/**
 * @brief Open file for redirection
 * @param path path to file
 * @param access_flag access flag, refer : https://shorturl.at/bflq8
 * @param open_flag open flag, refer : https://shorturl.at/fwPWY
 * @return int File descriptor, -1 when error
*/
int	redirect_open(char *path, int access_flag, int open_flag)
{
	int	fd;

	if (!access_file(path, access_flag))
		return (-1);
	fd = open(path, open_flag, S_IRWXU);
	if (fd < 0)
		return (print_error(path, ERR_OPEN), -1);
	return (fd);
}

/**
 * @brief Get file descriptor by entering prompt
 * @param delim delimiter
 * @return int File descriptor, -1 when error
*/
int	get_file_by_prompt_delim(char *delim)
{
	int		fd[2];
	char	*delim_modif;
	char	*buf;

	pipe(fd);
	delim_modif = ft_strjoin(delim, "\n");
	ft_putstr_fd("> ", 1);
	buf = get_next_line(0);
	if (buf == NULL)
	{
		close(fd[1]);
		close(fd[0]);
		return (free(delim_modif), print_error(NULL, ERR_MALLOC), -1);
	}
	while (buf && ft_strncmp(buf, delim_modif, ft_strlen(delim_modif)))
	{
		ft_putstr_fd(buf, fd[1]);
		free(buf);
		ft_putstr_fd("> ", 1);
		buf = get_next_line(0);
	}
	if (!buf)
		print_error(NULL, ERR_UNKNOWN);
	close(fd[1]);
	return (free(buf), fd[0]);
}
