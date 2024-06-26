/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:07:54 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/11 21:11:55 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_H
# define HANDLE_H

# include "minishell.h"
# include "lexer.h"

typedef struct s_pipe_run
{
	t_array	*array;
	size_t	index;
	int		pipe_fd[2];
	int		tmp_fd[2];
	int		fd[2];
}	t_pipe_run;

typedef struct s_wildcard_run
{
	t_array	*array;
	char	*word;
	t_shell	*shell;
	t_exec	*exec_cmd;
	size_t	index;
}	t_wildcard_run;

//utils
int		ms_wait_pipeline(t_shell *shell);
int		exit_pare_part(t_command *command,
			t_shell *shell, int fds[2]);

// expand fd
int		command_get_redir(t_array *array, t_exec *exec_cmd, t_shell *shell);

int		ms_heredoc_part(t_array *array, size_t *i, int *t_fd);
int		ms_redir_in_part(t_array *array, size_t *i, int *t_fd);
int		ms_append_part(t_array *array, size_t *i, int *t_fd);
int		ms_redir_out_part(t_array *array, size_t *i, int *t_fd);
void	ms_get_fd(t_array *array, t_shell *shell, int *fd);

// expand env
int		ms_expand(t_command *command, t_shell *shell,
			t_exec *exec_cmd, char **word);

int		ms_handle_join(t_array *array, t_shell *shell, int fd[2]);
int		ms_handle_pipe(t_array *array, t_shell *shell, int fd[2]);
int		ms_handle(t_array *array, t_shell *shell, int fd[2]);
int		ms_close_fd(int fd[2], int t_fd[2]);
#endif