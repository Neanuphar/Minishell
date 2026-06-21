/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:39:15 by aakli             #+#    #+#             */
/*   Updated: 2026/06/18 14:14:31 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int handle_quote(char *line, int *i, char *word, int *j)
{
    char quote;

    quote = line[*i];
    word[(*j)++] = quote;
    (*i)++;
    while (line[*i] && line[*i] != quote)
    {
        word[*j] = line[*i];
        (*i)++;
        (*j)++;
    }
    if (!line[*i])
        return (-1);
    word[(*j)++] = line[*i];
    (*i)++;
    return (0);
}

static int is_symbol(char c)
{
    return (c == ' ' || c == '\t' || c == '<' 
        || c == '>' || c == '&' || c == '|');
}

static void add_char(char *word, char *line, int *i, int *j)
{
    word[*j] = line[*i];
    (*i)++;
    (*j)++;
}

char *get_word(char *line, int *i)
{
    char *word;
    int j;

    j = 0;
    word = malloc(sizeof(char) * (ft_strlen(line) + 1));
    if (!word)
        return (NULL);
    while (line[*i] && !is_symbol(line[*i]))
    {
        if (line[*i] == '\'' || line[*i] == '"')
        {
            if (handle_quote(line, i, word, &j) == -1)
            {
                free(word);
                return (NULL);
            }
        }
        else
            add_char(word, line, i, &j);          
    }
    word[j] = '\0';
    return (word);
}
