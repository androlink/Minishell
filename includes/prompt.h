/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:44:12 by gcros             #+#    #+#             */
/*   Updated: 2024/04/24 14:09:50 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

typedef struct s_prompt_status {
    int     started;
    int     quote;
    int     squote;
    int     dquote;
    int     print;
    int     chevron;
    int     heredoc;
    int     operator;
    int     parenthesis;
    int     c_parenthesis;
    int     last_parenthesis;
    int     newline;
}   t_prompt_status;

typedef enum e_command_type {
    CMD_PIPE,
    CMD_REDIR_IN,
    CMD_REDIR_OUT,
    CMD_APPEND,
    CMD_HEREDOC,
    CMD_SEMICOLON,
    CMD_AND_IF,
    CMD_AND,
    CMD_OR,
    CMD_QUOTE,
    CMD_PARENTHESIS,
    CMD_EXPAND,
    CMD_TEXT,
    CMD_JOIN,
    CMD_WILDCARD
}  t_command_type;

union u_content{
    char    *str;
    t_array    *array;
    int     fd;
};
typedef struct s_command {
    t_command_type  type;
    union   u_content   content;
}  t_command;

t_command   *ms_parse_command(char *line);
int ms_prompt(t_shell *shell);
#endif