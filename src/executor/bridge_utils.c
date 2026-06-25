/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 05:57:33 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/24 22:50:57 by aakli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_heredoc(char *delim)
{
	char	*readed;
	char	*line;
	int		len_delim;

	len_delim = ft_strlen(delim);
	readed = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (g_signal_receivd == SIGINT)
		{
			free(line);
			free(readed);
			return (NULL);
		}
		if (line == NULL)
			return (readed);
		if (ft_strncmp(line, delim, len_delim) == 0 && line[len_delim] == '\0')
			return (free(line), readed);
		readed = append_char(readed, ft_strjoin(line, "\n"));
		free(line);
	}
}

int	fill_heredocs(t_node *node)
{
	t_redir	*redir;

	if (!node)
		return (1);
	if (node->type == NODE_PIPE)
	{
		if (!fill_heredocs(node->left))
			return (0);
		return (fill_heredocs(node->right));
	}
	redir = node->redirs;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			redir->heredoc_body = read_heredoc(redir->file);
			if (redir->heredoc_body == NULL)
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}
