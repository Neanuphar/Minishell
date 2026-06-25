/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/23 19:07:34 by aakli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_file(t_redir *redir, t_shell *shell)
{
	int		fd;
	int		pipefd[2];
	char	*body;

	if (redir->type == REDIR_IN)
		return (fd = open(redir->file, O_RDONLY));
	else if (redir->type == REDIR_OUT)
		return (fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redir->type == REDIR_APPEND)
		return (fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (redir->type == HEREDOC)
	{
		if (pipe(pipefd) == -1)
			return (-1);
		if (!redir->heredoc_quoted)
			body = expand_heredoc(redir->heredoc_body, shell);
		else
			body = redir->heredoc_body;
		write(pipefd[1], body, ft_strlen(body));
		if (!redir->heredoc_quoted)
			free(body);
		close(pipefd[1]);
		return (pipefd[0]);
	}
	return (-1);
}

int	apply_redirs(t_redir *redir, t_shell *shell)
{
	int	fd;

	while (redir)
	{
		fd = open_file(redir, shell);
		if (fd == -1)
			return (-1);
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
			dup2(fd, 0);
		else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			dup2(fd, 1);
		close(fd);
		redir = redir->next;
	}
	return (0);
}
