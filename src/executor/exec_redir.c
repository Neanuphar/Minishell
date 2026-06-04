/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/04 06:14:50 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int open_file(t_redir *redir)
{
	int fd;

	fd = -1;
	if (redir->type == REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->file,  O_WRONLY|O_CREAT|O_APPEND, 0644);
	return (fd);
}

int	apply_redirs(t_redir *redir)
{
	int fd;

	while (redir)
	{
		fd = open_file(redir);
		if (fd == -1)
			return(-1);
		if (redir->type == REDIR_IN)
		{
			dup2(fd, 0);
        	close(fd);
		}
		else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
			dup2(fd, 1);
        	close(fd);
		}
		redir = redir->next;
	}
	return (0);
}
