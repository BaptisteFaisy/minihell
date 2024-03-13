/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:27:50 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/13 21:04:18 by lhojoon          ###   ########.fr       */
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
static int	access_file(char *path, int type)
{
	int	access_result;

	access_result = access(path, type & (F_OK | R_OK | W_OK | X_OK));
	if (access_result == 0)
		return (0);
	if (errno == ENOENT && (type & F_SKIP_NUL) == F_SKIP_NUL)
		return (0);
	if (is_directory(path))
		return (basherr(path, ERR_IS_DIR), EXEC_IS_DIR);
	return (basherr(path, NULL), EXEC_FAILURE);
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

	fd = access_file(path, access_flag);
	if (fd != 0)
		return (-fd);
	fd = open(path, open_flag, S_IRWXU);
	if (fd < 0)
		return (basherr(path, ERR_OPEN), -EXEC_FAILURE);
	return (fd);
}

static void	gnl_prompt_handle(char **buf)
{
	__sighandler_t	sig[2];

	sig[0] = signal(SIGINT, sigint_handler_heredoc);
	sig[1] = signal(SIGQUIT, sigquit_handler_heredoc);
	*buf = readline("> ");
	signal(SIGINT, sig[0]);
	signal(SIGQUIT, sig[1]);
}

static int	handle_buf_null(char *delim_modif, int *fd)
{
	free(delim_modif);
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (g_status == -1)
		return (-EXEC_SIGINT);
	else
		return (basherr(NULL, WARN_HEREDOC_DELIM), 0);
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

	delim_modif = ft_strjoin(delim, "\n");
	gnl_prompt_handle(&buf);
	if (buf == NULL)
		return (handle_buf_null(delim_modif, NULL));
	if (pipe(fd) == -1)
		return (free(delim_modif), free(buf),
			print_error(NULL, ERR_PIPE), -EXEC_FAILURE);
	while (buf != NULL && ft_strncmp(buf, delim_modif, ft_strlen(delim_modif)))
	{
		ft_putstr_fd(buf, fd[1]);
		free(buf);
		gnl_prompt_handle(&buf);
	}
	if (buf == NULL)
		return (handle_buf_null(delim_modif, fd));
	close(fd[1]);
	return (free(delim_modif), free(buf), fd[0]);
}
