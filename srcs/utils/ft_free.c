/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:05:26 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/05 17:38:07 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	free_commands(t_array *array)
{
	size_t		i;
	t_command	*command;

	i = 0;

	if (!array)
		return (1);
	while (i < array->size)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_TEXT || command->type == CMD_EXPAND
			|| command->type == CMD_QUOTE || command->type == CMD_EXPAND_QUOTE)
			free(command->content.str);
		else if (command->type == CMD_HEREDOC || command->type == CMD_EMPTY
			|| command->type == CMD_REDIR_IN || command->type == CMD_REDIR_OUT
			|| command->type == CMD_APPEND || command->type == CMD_WILDCARD)
			(void)"void";
		else
			free_commands(command->content.array);
		free(command);
		i++;
	}
	ft_arr_free(&array, NULL);
	return (0);
}

void	free_prompt(t_shell *shell)
{
	ft_arr_free(&shell->cursor_array, NULL);
	ft_arr_free(&shell->heredoc_fd, NULL);
	free_commands(shell->commands);
	if (shell->command)
		free(shell->command);
	shell->command = NULL;
	shell->cursor = NULL;
	free(shell->prompt);
}

void	free_shell(t_shell *shell)
{
	free_prompt(shell);
	ms_env_collapse(&shell->env);
}

void	free_exec(t_exec	*exec)
{
	ft_arr_free(&exec->content, free);
	free(exec);
}
