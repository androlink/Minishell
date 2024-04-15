/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:58 by mmorot            #+#    #+#             */
/*   Updated: 2024/04/15 20:47:02 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ms_prompt.c
 * @brief Fichier qui contient la fonction qui va lancer le prompt
 *
 */
#include "arr.h"
#include "char.h"
#include "conf.h"
#include "minishell.h"
#include "prompt.h"
#include "str.h"
// #include "num.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

int	ms_syntax_error(t_error error, char *msg, t_shell *shell)
{
	if (!shell->prompt_listen)
		return (0);
	if (error == E_SYNTAX_UPD_TOK)
	{
		printf(ERR_SYNTAX_UPD_TOK, msg);
		free(msg);
	}
	else if (error == E_SYNTAX_UPD_EOF)
		printf(ERR_SYNTAX_UPD_EOF);
	else if (error == E_SYNTAX_UPD_NLN)
		printf(ERR_SYNTAX_UPD_NLN);
	shell->prompt_listen = 0;
	return (0);
}

int	ft_include(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*select_str(char *str, size_t n)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	while (i < n)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	get_operator(char *str)
{
	if (!ft_strncmp(str, S_OR, ft_strlen(S_OR)))
		return (E_OR);
	if (!ft_strncmp(str, S_AND_IF, ft_strlen(S_AND_IF)))
		return (E_AND_IF);
	return (-1);
}


int	get_metachar(char *str)
{
	if (!ft_strncmp(str, S_AND, ft_strlen(S_AND)))
		return (E_AND);
	if (!ft_strncmp(str, S_PIPE, ft_strlen(S_PIPE)))
		return (E_PIPE);
	if (!ft_strncmp(str, S_SEMICOLON, ft_strlen(S_SEMICOLON)))
		return (E_SEMICOLON);
	return (-1);
}

int	pass_blank(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_include(BLANK, str[i]))
		i++;
	return (i);
}

int	pass_word(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_include(NO_WORD, str[i]))
		i++;
	return (i);
}

int	pass_name(const char *str)
{
	size_t	i;

	i = 1;
	while (str[i] && (ft_isdigit(str[i]) || ft_isalpha(str[i]) || ft_include("_", str[i])))
		i++;
	return (i);
}



t_type	get_type(char *str)
{
	if (!ft_include(NO_WORD, str[0]))
		return (E_WORD);
	if (ft_include(BLANK, str[0]))
		return (E_EMPTY);
	if (ft_include(PARENTHESIS, str[0]))
		return (E_PARENTHESIS);
	if (get_operator(str) != -1)
		return (E_OPERATOR);
	if (get_metachar(str) != -1)
		return (E_METACHAR);
    if (!ft_strncmp(str, S_QUOTE, ft_strlen(S_QUOTE)))
		return (E_QUOTE);
	if (!ft_strncmp(str, S_DQUOTE, ft_strlen(S_DQUOTE)))
		return (E_DQUOTE);
	if (!ft_strncmp(str, S_SQUOTE, ft_strlen(S_SQUOTE)))
		return (E_SQUOTE);
	if (!ft_strncmp(str, S_HEREDOC, ft_strlen(S_HEREDOC)))
		return (E_HEREDOC);
	if (!ft_strncmp(str, S_APPEND, ft_strlen(S_APPEND)))
		return (E_APPEND);
	if (!ft_strncmp(str, S_REDIR_OUT, ft_strlen(S_REDIR_OUT)))
		return (E_REDIR_OUT);
	if (!ft_strncmp(str, S_REDIR_IN, ft_strlen(S_REDIR_IN)))
		return (E_REDIR_IN);
	if (!ft_strncmp(str, S_COMMENT, ft_strlen(S_COMMENT)))
		return (E_COMMENT);
	if (!ft_strncmp(str, S_WILDCARD, ft_strlen(S_WILDCARD)))
		return (E_WILDCARD);
	if (!ft_strncmp(str, S_NEWLINE, ft_strlen(S_NEWLINE)))
		return (E_NEWLINE);
	if (!ft_strncmp(str, S_DOLLAR, ft_strlen(S_DOLLAR)))
		return (E_NAME);
	return (E_EOF);
}

int	next_indent(t_type value, char *str)
{
	if (value >= E_HEREDOC && value <= E_OPERATOR)
		return (2);
	if (value >= E_QUOTE && value <= E_COMMENT)
		return (1);
	if (value == E_WORD)
		return (pass_word(str));
	if (value == E_NAME)
		return (pass_name(str));
	if (value == E_EMPTY)
		return (pass_blank(str));
	return (-1);
}

int is_chevron(t_type type)
{
    if (type == E_REDIR_IN || type == E_REDIR_OUT || type == E_APPEND || type == E_HEREDOC)
        return (1);
    return (0);
}

int	get_line(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			j++;
		i++;
	}
	return (j);
}

int	add_fd(t_shell *shell)
{
	(void)shell;
	int		fd[2];
	// 0 = read
	// 1 = write

	if (pipe(fd) == -1)
	{
		perror(ERR_PIPE);
		return (1);
	}
	if (!ft_arr_append(shell->heredoc_fd, (void *)(intptr_t)fd[0]))
	{
		perror(ERR_MALLOC);
		return (1);
	}
	if (!ft_arr_append(shell->heredoc_fd, (void *)(intptr_t)fd[1]))
	{
		perror(ERR_MALLOC);
		return (1);
	}
	shell->heredoc_size += 2;
	return (0);
}

int is_semicolon(t_type type, char *line)
{
	if (type == E_METACHAR && ft_strncmp(line, ";", 1) == 0)
		return (1);
	return (0);
}

char *ft_strjoin_seperator(char *s1, char *s2, char *sep)
{
    char *new;
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(sep) + 1));
    if (!new)
        return (NULL);
    while (s1[i])
    {
        new[i] = s1[i];
        i++;
    }
    while (sep[j])
    {
        new[i] = sep[j];
        i++;
        j++;
    }
    j = 0;
    while (s2[j])
    {
        new[i] = s2[j];
        i++;
        j++;
    }
    new[i] = '\0';
    return (new);
}

int	ms_parser(char *line, t_prompt_status *status, t_shell *shell)
{
	size_t	i;
	size_t	len;
	size_t	verif;
	t_type	type;
    char    *newline;

	i = 0;   
	verif = ft_strlen(line);
	if (verif <= 0)
		return (0);

    if (shell->prompt_listen)
    {
        newline = shell->prompt;
        if (status->parenthesis)
		{
			if (status->print || status->parenthesis != status->last_parenthesis)
            	shell->prompt = ft_strjoin_seperator(shell->prompt, line, "; ");
			else
				shell->prompt = ft_strjoin_seperator(shell->prompt, line, " ");
		}
		else if (status->newline)
		{
			status->newline = 0;
			shell->prompt = ft_strjoin_seperator(shell->prompt, line, " ");
		}
        else
            shell->prompt = ft_strjoin_seperator(shell->prompt, line, "\n");
        replace_history_entry(shell->line, shell->prompt, NULL);
        //Fonction utiliser en bonus
        free(newline);
    }
    
    shell->prompt_listen = 1;
	while (line[i])
	{
		type = get_type(&line[i]);
		if (type == E_EOF)
			break ;
		len = next_indent(type, &line[i]);

        //error
        if (!status->quote && !status->squote && !status->dquote)
        {
            if (type >= E_METACHAR && type <= E_OPERATOR && !is_chevron(type) && status->operator == 1 && !status->c_parenthesis)
			{
                ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
			}
            if (type >= E_PARENTHESIS && type <= E_OPERATOR && !is_chevron(type) && status->chevron == 1)
                ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
            if (is_chevron(type) && status->chevron == 1)
                ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
            if ((type == E_METACHAR || type == E_OPERATOR) && status->print == 0 && !status->c_parenthesis)
			{
                ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
			}
        
            if (type == E_WORD || type == E_NAME)
            {
                status->print = 1;
                status->operator = 0;
				status->chevron = 0;
                status->newline = 0;
				status->c_parenthesis = 0;
            }

			if (type == E_HEREDOC)
			{
				status->heredoc = 1;
				status->print = 0;
			}

			if (status->heredoc && status->print)
			{
				shell->limiter = select_str(&line[i], len);
				if (add_fd(shell))
					return (0);
				while (1)
				{
					newline = readline("heredoc> ");
					if (!newline)
						break ;
					if (ft_strlen(shell->limiter) == ft_strlen(newline) && ft_strncmp(newline, shell->limiter, ft_strlen(shell->limiter)) == 0)
					{
						free(newline);
						break ;
					}
					write(
						(int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 2], 
						newline, 
						ft_strlen(newline));
					free(newline);
				}
				close((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 2]);
			}

            if (type >= E_PARENTHESIS && type <= E_OPERATOR)
            {
				status->newline = 0;
                status->c_parenthesis = 0;
				status->print = 0;
                if (is_chevron(type))
                    status->chevron = 1;
                else
				{
					if (type == E_OPERATOR)
						status->newline = 1;
					else if (type == E_METACHAR && ft_strncmp(&line[i], "|", 1) == 0)
						status->newline = 1;
                    status->operator = 1;
				}
            }

            if (type == E_NEWLINE)
            {
                if (status->print == 0)
                    ms_syntax_error(E_SYNTAX_UPD_EOF, NULL, shell);
                status->print = 0;
				status->c_parenthesis = 0;
            }

            if (type == E_COMMENT)
                break ;

            if (type == E_PARENTHESIS)
            {
				status->newline = 0;
				status->c_parenthesis = 0;
                if (ft_strncmp(&line[i], "(", 1) == 0)
                {
					status->parenthesis += 1;
					status->last_parenthesis = status->parenthesis;
				}
                else
                {
					status->c_parenthesis = 1;
                    if (status->parenthesis == 0)
                        ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
                    else
					{
						status->last_parenthesis = status->parenthesis;
                        status->parenthesis -= 1;
					}
                
                }
            }
        }

        if (type == E_QUOTE && !(status->dquote || status->squote))
            status->quote = !status->quote;
        if (type == E_SQUOTE  && !(status->dquote || status->quote))
            status->squote = !status->squote;
        if (type == E_DQUOTE  && !(status->quote || status->squote))
            status->dquote = !status->dquote;

        

        //end error
        if (shell->prompt_listen == 0)
            break ;
		if (DEBUG_MODE)
        	printf(C_YELLOW"type: %d | is: %s | p: %d\n", type, select_str(&line[i], len),  status->parenthesis);
		if (type != E_EMPTY)
		{
			if (status-> print && status->heredoc)
			{
				ft_arr_append(shell->commands, ft_strjoin("<< ",ft_itoa((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1])));
				status->heredoc = 0;
			}
			else if(!status->heredoc)
				ft_arr_append(shell->commands, select_str(&line[i], len));
		}
		i += len;
        len = 0;
	}
    if (status->chevron)
        ms_syntax_error(E_SYNTAX_UPD_NLN, NULL, shell);
    
    if (shell->prompt_listen == 0)
        return (0);
	
    while (status->heredoc || status->quote || status->squote || status->dquote || status->parenthesis || status->newline)
    {

		newline = readline("> ");
		if (!newline)
			break ;
		ms_parser(newline, status, shell);
		if (shell->prompt_listen == 0)
			break ;
		// free(newline);
    }
	if (DEBUG_MODE)
    	printf(C_BLUE"indent: "C_WHITE"%zu | %zu\n"C_RESET, i, verif);
	return (1);
}



/**
 * @brief Fonction qui va recupérer les commandes de l'utilisateur et les executer
 *
 * @param shell Structure principal du programme
 * @return int **0** si tout c'est bien passé sinon **1**
 */
int	ms_prompt(t_shell *shell)
{
	char			*line;
	t_prompt_status	status;

	shell->line = 0;
	while (1)
	{
        status = (t_prompt_status){0};
		line = readline(MS_NAME"$ ");
		shell->heredoc_fd = ft_arr_new(10);
		shell->heredoc_size = 0;
		shell->commands = ft_arr_new(10);
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
            shell->prompt_listen = 0;
			status = (t_prompt_status){0};
            shell->prompt = ft_strdup(line);
			ms_parser(line, &status, shell);
			if (DEBUG_MODE)
			{
            	printf(C_RED"%s\n"C_RESET, shell->prompt);
				printf(C_GREEN"FD: %d\n"C_RESET, shell->heredoc_size/2);
				// print list heredoc
				int i = 0;
				while (shell->heredoc_size > 0 && i <= shell->heredoc_size/2)
				{
					printf(C_BLUE"- FD: %d | %d\n"C_RESET, (int)(intptr_t)shell->heredoc_fd->data[i], (int)(intptr_t)shell->heredoc_fd->data[i+1]);
					i+=2;
				}
				// read FD heredoc
				i = 1;
				while (shell->heredoc_size > 0 && i <= shell->heredoc_size)
				{
					char *buffer = malloc(sizeof(char) * 100);
					read((int)(intptr_t)shell->heredoc_fd->data[i], buffer, 100);
					printf(C_BLUE"%s\n"C_RESET, buffer);
					free(buffer);
					i += 2;
				}
				printf("--------------------\n");
				while (shell->commands->size > 0)
				{
					printf(C_YELLOW"%s\n"C_RESET, (char *)shell->commands->data[0]);
					free(shell->commands->data[0]);
					ft_arr_shift(shell->commands);
				}
			}
			
            shell->line++;
		}
		free(line);
	}
	return (0);
}