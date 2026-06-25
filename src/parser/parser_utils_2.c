/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 21:05:06 by aakli             #+#    #+#             */
/*   Updated: 2026/06/25 06:44:24 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	return_token(t_token *token)
{
	while (token && token->next)
	{
		if (token->type == REDIR_IN && token->next->type != WORD)
			return (print_error(token->next), -1);
		if (token->type == REDIR_OUT && token->next->type != WORD)
			return (print_error(token->next), -1);
		if (token->type == REDIR_APPEND && token->next->type != WORD)
			return (print_error(token->next), -1);
		if (token->type == HEREDOC && token->next->type != WORD)
			return (print_error(token->next), -1);
		if (token->type == PIPE && token->next->type == PIPE)
			return (print_error(token->next), -1);
		token = token->next;
	}
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_APPEND || token->type == HEREDOC
		|| token->type == PIPE)
	{
		write(2, "minishell: syntax error near unexpected token `newline'\n",
			56);
		return (-1);
	}
	return (0);
}

void	add_heredoc_redir(t_cmd *cmd, char *delim)
{
	char	quote;
	char	*stripped;
	t_redir	*redir;

	quote = delim[0];
	if (quote == '\'' || quote == '"')
	{
		stripped = ft_substr(delim, 1, ft_strlen(delim) - 2);
		add_redir(cmd, HEREDOC, stripped);
		free(stripped);
		redir = cmd->redirs;
		while (redir->next)
			redir = redir->next;
		redir->heredoc_quoted = 1;
	}
	else
		add_redir(cmd, HEREDOC, delim);
}