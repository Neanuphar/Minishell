/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 00:11:40 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/13 04:45:06 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void free_cmds(t_cmd *cmd)
{
	t_cmd *next;

	while (cmd)
	{
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}

static	t_node	*create_cmd_node(t_cmd *cmd)
{
	t_node	*cmd_node;

	cmd_node = malloc(sizeof(t_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = NODE_CMD;
	cmd_node->argv = cmd->args;
	cmd_node->redirs = cmd->redirs;
	cmd_node->left = NULL;
	cmd_node->right = NULL;
	return (cmd_node);
}

static t_node *cmd_to_node(t_cmd *cmd)
{
	t_node	*node;

	if (cmd->next == NULL)
		return(create_cmd_node(cmd));
	node = malloc(sizeof(t_node));
	if(!node)
		return (NULL);
	else
	{
		node->type = NODE_PIPE;
		node->argv = NULL;
		node->redirs = NULL;
		node->left = create_cmd_node(cmd);
		node->right = cmd_to_node(cmd->next);
	}
	return (node);
}

t_node	*bridge(char *input)
{
	t_token *tokens;
	t_cmd *cmds;
	t_node *ast;

	tokens = lexer(input);
	if(!tokens)
		return (NULL);
	cmds = parse_tokens(tokens);
	if(!cmds)
		return (free_token_list(tokens), NULL);
	free_token_list(tokens);
	ast = cmd_to_node(cmds);
	free_cmds(cmds);
	return(ast);
}
