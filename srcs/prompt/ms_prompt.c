/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:58 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 22:01:28 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ms_prompt.c
 * @brief Fichier qui contient la fonction qui va lancer le prompt
 *
 */
#include "conf.h"
#include "minishell.h"
#include "parser.h"
#include "handle.h"
#include "exec.h"
#include "put.h"
#include "get_next_line.h"

static	void	ms_prompt_init(t_shell *shell)
{
	shell->line = 0;
	shell->status = 0;
	shell->arb_pipe = 0;
	shell->in_pipe = 0;
}

static	int	ms_prompt_handle(t_shell *shell, char *line)
{
	t_prompt_s	status;

	status = (t_prompt_s){0};
	shell->heredoc_fd = ft_arr_new(10);
	shell->heredoc_size = 0;
	shell->commands = ft_arr_new(10);
	shell->cursor = shell->commands;
	shell->cursor_array = ft_arr_new(10);
	if (!line || !shell->commands || !shell->heredoc_fd
		|| !shell->commands)
		return (free_prompt(shell), 1);
	if (line[0] != '\0')
	{
		add_history(line);
		shell->prompt_listen = 0;
		status = (t_prompt_s){0};
		shell->prompt = ft_strdup(line);
		ms_parser(line, &status, shell);
		ms_handle(shell->commands, shell, (int [2]){0, 1});
		if (DEBUG_MODE)
			ms_debug(shell);
		shell->line++;
	}
	free_prompt(shell);
	return (0);
}

char	*next_line(char *prompt)
{
	char	*str;

	str = NULL;
	if (isatty(0))
		str = readline(prompt);
	else
		str = get_next_line(0);
	return (str);
}

int	ms_prompt(t_shell *shell)
{
	char	*line;

	ms_prompt_init(shell);
	while (1)
	{
		ms_sig_set(sig_prompt);
		line = next_line(MS_NAME"$ ");
		if (line == NULL)
			break ;
		ms_sig_set(sig_exec);
		g_signal_value = 0;
		if (!ms_prompt_handle(shell, line))
			free(line);
		if (g_signal_value != 0)
			ft_putchar_fd('\n', 2);
	}
	return (0);
}
