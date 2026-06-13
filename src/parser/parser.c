/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:01:27 by aakli             #+#    #+#             */
/*   Updated: 2026/06/11 15:33:15 by aakli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd *new_command(void)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->next = NULL;
    cmd->redirs = NULL;
    return (cmd);
}

void add_arguments(t_cmd *cmd, char *word)
{
    char **new_args;
    int count;
    int i = 0;

    count = count_args(cmd);
    new_args = malloc(sizeof(char *) * (count + 2));
    if (!new_args)
        return;
    while (i < count)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    new_args[i] = ft_strdup(word);
    new_args[i + 1] = NULL;
    free(cmd->args);
    cmd->args = new_args;
    return;
}

void add_redir(t_cmd *cmd, t_token_type type, char *file)
{
    t_redir *new_redir;
    t_redir *current;

    new_redir = malloc(sizeof(t_redir));
    if (!new_redir)
        return;
    new_redir->type = type;
    new_redir->file = ft_strdup(file);
    new_redir->heredoc_body = NULL;
    new_redir->heredoc_quoted = 0;
    new_redir->next = NULL;
    if (cmd->redirs == NULL)
    {
        cmd->redirs = new_redir;
        return;
    }
    current = cmd->redirs;
    while (current->next)
        current = current->next;
    current->next = new_redir;
}

t_cmd *parse_tokens(t_token *token)
{
    t_cmd *cmd_to_return;
    t_cmd *tmp;
    
    if (!token)
        return (NULL);
    cmd_to_return = new_command();
    tmp = cmd_to_return;
    if(check_order(token) != 0)
        return(free_cmd_list(tmp), NULL);
    while (token)
    {
        if (token->type == WORD)
            add_arguments(tmp, token->value);
        if (token->type == REDIR_IN || token->type == REDIR_OUT 
            || token->type == REDIR_APPEND || token->type == HEREDOC)
            add_redir(tmp, token->type, token->next->value);
        if(token->type == PIPE)
        {
            tmp->next = new_command();
            tmp = tmp->next;
        }
        token = token->next;
    }
    return(cmd_to_return);
}
