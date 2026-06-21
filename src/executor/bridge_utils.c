/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 05:57:33 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/21 08:42:38 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *read_heredoc(char *delim)
{
	char *readed;
	char *line;
	int len_delim;
	
	len_delim = ft_strlen(delim);
	readed = ft_strdup("");
	while(1)
	{
		line = readline("> ");
		if(ft_strncmp(line, delim, len_delim) == 0 && line[len_delim] == '\0')
			return(free(line), readed);
		readed = append_char(readed, ft_strjoin(line, "\n"));
		free(line);
	}
}

void fill_heredocs(t_node *node)
{
	t_redir *redir;
	
	if (!node)
		return;
	if (node->type == NODE_PIPE)
	{
		fill_heredocs(node->left);
		fill_heredocs(node->right);
		return;	
	}
	redir = node->redirs;
	while (redir)
	{
		if (redir->type == HEREDOC)
			redir->heredoc_body = read_heredoc(redir->file);
		redir = redir->next;
	}
}