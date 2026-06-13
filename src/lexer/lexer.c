/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:32:33 by aakli             #+#    #+#             */
/*   Updated: 2026/06/03 14:28:09 by aakli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *new_token(t_token_type type, char *value)
{
    t_token *tokens;

    tokens = malloc(sizeof(t_token));
    if (tokens == NULL)
        return (NULL);
    tokens->type = type;
    tokens->value = value;
    tokens->next = NULL;
    return (tokens);
}

void add_token(t_token **list, t_token *new)
{
    t_token *current;

    current = *list;
    if (*list == NULL)
    {
        *list = new;
        return;
    }
    while (current->next)
        current = current->next;
    current->next = new;
}

static void handle_add_token(t_token **list, char *line, int *i)
{
    if (line[*i] == '|')
    {
        add_token(list, new_token(PIPE, NULL));
        (*i)++;
    }
    else if (line[*i] == '<' && line[*i + 1] == '<')
    {
        add_token(list, new_token(HEREDOC, NULL));
        (*i) += 2;
    }
    else if (line[*i] == '>' && line[*i + 1] == '>')
    {
        add_token(list, new_token(REDIR_APPEND, NULL));
        (*i) += 2;
    }
    else if (line[*i] == '>')
    {
        add_token(list, new_token(REDIR_OUT, NULL));
        (*i)++;
    }
    else if (line[*i] == '<')
    {
        add_token(list, new_token(REDIR_IN, NULL));
        (*i)++;
    }
}
t_token *lexer(char *line)
{
    t_token *list;
    char *word;
    int i;

    i = 0;
    list = NULL;
    while (line[i])
    {
        if (line[i] == ' ' || line[i] == '\t')
            i++;
        else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
            handle_add_token(&list, line, &i);
        else
        {
            word = get_word(line, &i);
            if(!word)
            {
                printf("minishell: unclosed quote\n");
                free_token_list(list);
                return(NULL);       
            }
            add_token(&list, new_token(WORD, word));
        }
    }
    return (list);
}
