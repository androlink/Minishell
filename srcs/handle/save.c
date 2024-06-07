/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:53:53 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/07 17:00:39 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "conf.h"
#include "arr.h"
#include "lexer.h"
#include <sys/stat.h>
#include "env.h"
#include "exec.h"
#include "utils.h"
#include "handle.h"

static int	add_word(t_command *command, char **word, t_shell *shell)
{
	char	*tmp;

	if (*word == NULL)
		*word = ft_strdup(command->content.str);
	else
	{
		tmp = *word;
		*word = ft_strjoin(*word, command->content.str);
		free(tmp);
	}
	if (*word == NULL)
	{
		shell->error = 1;
		shell->prompt_listen = 0;
		return (1);
	}
	return (0);
}

static int	commit_word(t_exec *exec_cmd, char **word)
{
	if (*word != NULL)
	{
		ft_arr_append(exec_cmd->content, *word);
		*word = NULL;
	}
	return (0);
}

// static int ms_wildcard(t_array *array, size_t *i, t_exec *exec_cmd, char **word)
// {
// 	t_command	*command;
// 	char		*str;
// 	char		*path;
// 	char		*tmp;
// 	command = (t_command *)array->data[*i];
	
// 	if (word != NULL)
// 	{
// 		str = ft_strjoin(*word, "*");
// 		free(*word);
// 		*word = NULL;
// 	}
// 	else
// 		str = ft_strdup("*");
// 	if (str == NULL)
// 		return (1);
	
// 	while ((*i + 1) < array->size )
// 	{
// 		if (((t_command *)array->data[*i + 1])->type == CMD_WILDCARD)
// 		{
// 			tmp = ft_strjoin(str, "*");
// 			free(str);
// 			str = tmp;
// 			*i += 1;
// 		}
// 		else if (((t_command *)array->data[*i + 1])->type == CMD_TEXT)
// 		{
// 			tmp = ft_strjoin(str, ((t_command *)array->data[*i + 1])->content.str);
// 			free(str);
// 			str = tmp;
// 			*i += 1;
// 		}
// 		else
// 			break;
// 	} 
	



// 	if (path == NULL)
// 	{
// 		*i += 1;
// 		return (0);
// 	}


// 	path = ms_pathexp(command->content.str);
// 	ft_arr_append(exec_cmd->content, path);
// 	free(path);
// 	*i += 1;
// 	return (0);
// }

static int	add_exec(t_exec **exec_cmd, t_shell *shell);

static int	run_wildcard(t_wildcard_run *run)
{
	t_command	*command;
	char		*tmp;

	while (run->index < run->array->size && run->shell->error < 1)
	{
		command = (t_command *)run->array->data[run->index];
		if (run->exec_cmd->content->size > 0)
			return (1);
		if (command->type == CMD_TEXT)
			add_word(command, &run->word, run->shell);
		else if (command->type == CMD_EXPAND
			|| command->type == CMD_EXPAND_QUOTE)
			ms_expand(command, run->shell, run->exec_cmd, &run->word);
		else if (command->type == CMD_WILDCARD)
		{
			tmp = run->word;
			run->word = ft_strjoin(run->word, "*");
			if (run->word == NULL)
			{
				run->shell->error = 1;
				run->shell->prompt_listen = 0;
				free(tmp);
				return (0);
			}
			free(tmp);
		}
		else
			return (1);
		run->index++;
	}
	return (0);
}

static t_wildcard_run	*ms_handle_wildcard(t_shell *shell, t_array *array,
	size_t *i, char **word)
{
	t_wildcard_run	*run;

	if (!shell->prompt_listen)
		return (NULL);
	run = malloc(sizeof(t_wildcard_run));
	if (run == NULL)
	{
		shell->error = 1;
		shell->prompt_listen = 0;
		return (NULL);
	}
	if (add_exec(&run->exec_cmd, shell) == 0 || run->exec_cmd == NULL)
	{
		free(run);
		return (NULL);
	}
	run->index = *i;
	run->array = array;
	run->shell = shell;
	run->word = *word;
	// printf("IN2 wildcard\n");
	run_wildcard(run);
	return (run);
}

#include "wildcard.h"

static int swap_wildcard(char *pattern, t_array *array)
{
	t_array *tmp_array;

	tmp_array = ms_pathexp(pattern);
	if (tmp_array == NULL)
		return (1);
	if (ft_arr_resize(array, array->size + tmp_array->size + 20))
	{
		while (tmp_array->size > 0)
		{
			ft_arr_push(array, ft_arr_shift(tmp_array));
		}
	}
	ft_arr_free(&tmp_array, free);
	return (0);
}

static int ms_wildcard(t_array *array, size_t *i, t_exec *exec_cmd, char **word, t_shell *shell)
{
	t_wildcard_run	*run;
	(void) exec_cmd;
	
	//printf("IN wildcard\n");
	if (*word == NULL)
	{
		*word = ft_strdup("");
		if (*word == NULL)
			return (1);
	}
	run = ms_handle_wildcard(shell, array, i, word);
	//printf("OUT wildcard\n");
	if (run == NULL)
		return (0);

	//printf("COUCOU1\n");
	
	if (run->exec_cmd->content->size > 0)
	{
		char *tmp;
		swap_wildcard((char *)run->exec_cmd->content->data[0], exec_cmd->content);
		tmp = NULL;
		if (tmp != NULL)
			ft_arr_append(exec_cmd->content, tmp);
		free(ft_arr_shift(run->exec_cmd->content));
		size_t i = 0;
		while (i < run->exec_cmd->content->size)
		{
			ft_arr_append(exec_cmd->content, run->exec_cmd->content->data[i]);
			i++;
		}
		*word = run->word;
	}
	else
	{
		swap_wildcard(run->word, exec_cmd->content);
		// ms_pathexp(run->word);
		*word = NULL;
	}
	*i = run->index;
	// word = NULL;
	// free(run->exec_cmd);
	// free(run);

	return (0);
}

//last

// static int	run_join(t_array *array, t_exec *exec_cmd,
// 	t_shell *shell, char **word)
// {
// 	size_t		i;
// 	t_command	*command;

// 	i = 0;
// 	while (i < array->size && shell->error < 1)
// 	{
// 		command = (t_command *)array->data[i];
// 		if (command->type == CMD_TEXT)
// 			add_word(command, word, shell);
// 		else if (command->type == CMD_EXPAND
// 			|| command->type == CMD_EXPAND_QUOTE)
// 			ms_expand(command, shell, exec_cmd, word);
// 		else if (command->type == CMD_WILDCARD)
// 			ms_wildcard(array, &i, exec_cmd, word, shell);
// 		else if (command->type == CMD_EMPTY)
// 			commit_word(exec_cmd, word);
// 		else if (command->type == CMD_HEREDOC)
// 			ms_heredoc_part(array, &i, exec_cmd->fd);
// 		else if (command->type == CMD_REDIR_IN)
// 			ms_redir_in_part(array, &i, exec_cmd->fd);
// 		else if (command->type == CMD_REDIR_OUT)
// 			ms_redir_out_part(array, &i, exec_cmd->fd);
// 		else if (command->type == CMD_APPEND)
// 			ms_append_part(array, &i, exec_cmd->fd);
// 		i++;
// 	}
// 	return (0);
// }

static int add_exec_heredoc(t_exec *exec, t_command *command)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (1);
	new_command->type = CMD_HEREDOC;
	new_command->content.fd = command->content.fd;
	if (ft_arr_append(exec->redir, new_command) == 0)
	{
		free(new_command);
		return (1);
	}
	command->type = CMD_EMPTY;
	return (0);
}

static char *command_get_path(t_array *array, size_t *i, t_shell *shell)
{
	t_command	*command;
	char		*path;
	int			count;

	count = 0;
	if (*i >= array->size)
		return (NULL);
	*i += 1;
	while (*i < array->size && shell->error < 1)
	{
		command = (t_command *)array->data[*i];
		if (command->type == CMD_EMPTY && count > 0)
			return (path);
		else if (command->type == CMD_TEXT)
		{
			path = command->content.str;
			command->type = CMD_EMPTY;
			command->content.str = NULL;
		}
		// else if (command->type == CMD_EXPAND
		// 	|| command->type == CMD_EXPAND_QUOTE)
		*i += 1;
		count++;
	}
	*i -= 1;
	return (path);
}

static int add_exec_redir(t_exec *exec, t_array *array, size_t *i, t_shell *shell)
{
	t_command	*command;
	t_command	*new_command;
	char		*path;

	command = (t_command *)array->data[*i];
	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (1);
	new_command->type = command->type;
	path = command_get_path(array, i, shell);
	if (path == NULL)
	{
		free(new_command);
		return (1);
	}
	new_command->content.str = path;
	if (ft_arr_append(exec->redir, new_command) == 0)
	{
		free(new_command);
		return (1);
	}
	command->type = CMD_EMPTY;
	return (0);
}

static int	command_get_redir(t_array *array, t_exec *exec_cmd, t_shell *shell)
{
	size_t		i;
	t_command	*command;

	i = 0;
	while (i < array->size && shell->error < 1)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_HEREDOC)
		{
			add_exec_heredoc(exec_cmd, command);
		}
		else if (command->type >= CMD_REDIR_IN && command->type <= CMD_APPEND)
			add_exec_redir(exec_cmd, array, &i, shell);
		i++;
	}
	return (0);
}
//new
static int	run_join(t_array *array, t_exec *exec_cmd,
	t_shell *shell, char **word)
{
	size_t		i;
	t_command	*command;

	i = 0;
	command_get_redir(array, exec_cmd, shell);
	while (i < array->size && shell->error < 1)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_TEXT)
			add_word(command, word, shell);
		else if (command->type == CMD_EXPAND
			|| command->type == CMD_EXPAND_QUOTE)
			ms_expand(command, shell, exec_cmd, word);
		else if (command->type == CMD_WILDCARD)
			ms_wildcard(array, &i, exec_cmd, word, shell);
		else if (command->type == CMD_EMPTY)
			commit_word(exec_cmd, word);
		i++;
	}	
	return (0);
}

static int	add_exec(t_exec **exec_cmd, t_shell *shell)
{
	*exec_cmd = malloc(sizeof(t_exec));
	if (exec_cmd == NULL)
	{
		shell->error = 1;
		return (shell->prompt_listen = 0);
	}
	(*exec_cmd)->content = ft_arr_new(20);
	(*exec_cmd)->redir = ft_arr_new(20);
	if ((*exec_cmd)->content == NULL || (*exec_cmd)->redir == NULL)
	{
		free(*exec_cmd);
		exec_cmd = NULL;
		shell->error = 1;
		return (shell->prompt_listen = 0);
	}
	(*exec_cmd)->fd[0] = -1;
	(*exec_cmd)->fd[1] = -1;
	return (1);
}

int	ms_handle_join(t_array *array, t_shell *shell, int fd[2])
{
	t_exec		*exec_cmd;
	char		*word;

	if (!shell->prompt_listen || g_signal_value != 0)
	{
		return (0);
	}
	word = NULL;
	if (add_exec(&exec_cmd, shell) == 0 || exec_cmd == NULL)
		return (0);
	run_join(array, exec_cmd, shell, &word);
	if (exec_cmd->fd[0] == -1)
		exec_cmd->fd[0] = fd[0];
	if (exec_cmd->fd[1] == -1)
		exec_cmd->fd[1] = fd[1];
	if (word != NULL)
		ft_arr_append(exec_cmd->content, word);
	if (exec_cmd->content->size > 0)
		ms_set_status(ms_exec(exec_cmd, shell));
	ms_close_fd(fd, exec_cmd->fd);
	if (DEBUG_MODE == 1)
	{
		printf("DEBUG MODE | REDIR\n");
		ms_debug_command_to_json_exec(0, exec_cmd->redir);
	}
	free_exec(exec_cmd);
	return (1);
}
