/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:01:27 by aakli             #+#    #+#             */
/*   Updated: 2026/06/25 06:57:35 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*new_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->redirs = NULL;
	return (cmd);
}

void	add_arguments(t_cmd *cmd, char *word)
{
	char	**new_args;
	int		count;
	int		i;

	i = 0;
	count = count_args(cmd);
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(word);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return ;
}

void	add_redir(t_cmd *cmd, t_token_type type, char *file)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	new_redir->heredoc_body = NULL;
	new_redir->heredoc_quoted = 0;
	new_redir->next = NULL;
	if (cmd->redirs == NULL)
	{
		cmd->redirs = new_redir;
		return ;
	}
	current = cmd->redirs;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

static int	norm_parse_token(t_token *token, t_cmd *tmp)
{
	while (token)
	{
		if (token->type == WORD)
			add_arguments(tmp, token->value);
		if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == REDIR_APPEND || token->type == HEREDOC)
		{
			if (!token->next)
				return (1);
			if (token->type == HEREDOC)
				add_heredoc_redir(tmp, token->next->value);
			else
				add_redir(tmp, token->type, token->next->value);
			token = token->next;
		}
		if (token->type == PIPE)
		{
			tmp->next = new_command();
			if (!tmp->next)
				return (1);
			tmp = tmp->next;
		}
		token = token->next;
	}
	return (0);
}

t_cmd	*parse_tokens(t_token *token)
{
	t_cmd	*tmp;
	t_cmd	*cmd_to_return ;

	if (!token)
		return (NULL);
	cmd_to_return = new_command();
	if (!cmd_to_return)
		return (NULL);
	tmp = cmd_to_return ;
	if (check_order(token) != 0)
		return (free_cmd_list(tmp), NULL);
	if (norm_parse_token(token, tmp) != 0)
		return (free_cmd_list(cmd_to_return), NULL);
	return (cmd_to_return);
}
