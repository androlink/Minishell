/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:55:26 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/12 13:38:35 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

void	ms_lexer(t_shell *shell, t_prompt_s *status,
			int type, t_parser_str *str)
{
	if (type == E_HEREDOC)
		ms_lexer_heredoc_add(shell, status);
	else if (type == E_NAME)
		ms_lexer_name(shell, status, str);
	else if (status->squote || status->dquote)
		ms_lexer_quote(shell, status, str);
	else if (type == E_REDIR_IN || type == E_REDIR_OUT || type == E_APPEND)
		ms_lexer_redir(shell, status, str);
	else if (type == E_WILDCARD)
		ms_lexer_wildcard(shell, str);
	else if (type == E_EMPTY)
		ms_lexer_empty(shell, status);
	else if (type != E_PARENTHESIS)
		ms_lexer_operator(shell, status, str);
}
