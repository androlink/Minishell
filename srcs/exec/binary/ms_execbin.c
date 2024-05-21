/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execbin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:52:43 by gcros             #+#    #+#             */
/*   Updated: 2024/05/11 04:43:46 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "str.h"
#include "put.h"

int		on_error(char **envp, char **arg, char *cmd);
char	**get_env(t_env	*env);
char	**get_args(t_array *arr);
int		run_bin(char *cmd, char **args, char **envp);

int	execbin(t_exec *exec, t_shell *shell)
{
	char	**args;
	char	**envp;
	char	*cmd;

	cmd = NULL;
	args = NULL;
	envp = NULL;
	set_io(exec->fd);
	args = get_args(exec->content);
	envp = get_env(shell->env);
	if (args != NULL)
		cmd = get_bin(args[0], shell->env);
	if ((!(size_t)args | !(size_t)envp | !(size_t)cmd))
		return (on_error(envp, args, cmd));
	free_shell(shell);
	free_exec(exec);
	return (run_bin(cmd, args, envp));
}

int	run_bin(char *cmd, char **args, char **envp)
{
	ft_putendl_fd("==run_bin", 2);
	execve(cmd, args, envp);
	return (EXIT_FAILURE);
}

char	**get_env(t_env *env)
{
	char	**envp;

	if (ms_env_to_strs(env, &envp) == 1)
		return (NULL);
	return (envp);
}

char	**get_args(t_array *arr)
{
	t_array	*new;
	char	**args;

	new = ft_arr_map(arr, (void *(*)(void *))ft_strdup, free);
	if (new == NULL)
		return (NULL);
	if (ft_arr_append(new, NULL) == 0)
		return (ft_arr_free(&arr, free), NULL);
	args = (char **)new->data;
	free(new);
	return (args);
}

int	on_error(char **envp, char **args, char *cmd)
{
	if (args != NULL)
		ft_strsfree(args);
	if (envp != NULL)
		ft_strsfree(envp);
	free(cmd);
	return (EXIT_FAILURE);
}