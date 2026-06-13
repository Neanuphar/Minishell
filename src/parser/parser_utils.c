/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:09:11 by aakli             #+#    #+#             */
/*   Updated: 2026/06/11 15:24:34 by aakli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_args(t_cmd *command)
{
    int i;
    i = 0;

    if (!command->args)
        return (0);
    while (command->args[i])
        i++;
    return (i);
}
void free_redirs_list(t_redir *redir)
{
    t_redir *tmp;
    while (redir)
    {
        tmp = redir->next;
        free(redir->file);
        free(redir);
        redir = tmp;
    }
}
void free_cmd_list(t_cmd *commande)
{
    t_cmd *tmp;
    int i;

    while (commande)
    {
        i = 0;
        tmp = commande->next;
        if (commande->args)
        {
            while (commande->args[i])
            {
                free(commande->args[i]);
                i++;
            }
        }
        free(commande->args);
        free_redirs_list(commande->redirs);
        free(commande);
        commande = tmp;
    }
}

void print_error(t_token *token)
{
    write(2, "minishell: syntax error near unexpected token `", 47);
    if (token->value)
        write(2, token->value, ft_strlen(token->value));
    else
    {
        if (token->type == PIPE)
            write(2, "|", 1);
        else if (token->type == REDIR_IN)
            write(2, "<", 1);
        else if (token->type == REDIR_OUT)
            write(2, ">", 1);
        else if (token->type == REDIR_APPEND)
            write(2, ">>", 2);
        else if (token->type == HEREDOC)
            write(2, "<<", 2);
    }
    write(2, "'\n", 2);
}
int check_order(t_token *token)
{
    if (!token)
        return (-1);
    if (token->type == PIPE)
        return (print_error(token), -1);
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
        token = token->next;
    }
    if (token->type == REDIR_IN || token->type == REDIR_OUT ||
        token->type == REDIR_APPEND || token->type == HEREDOC)
    {
        write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
        return (-1);
    }
    return (0);
}
