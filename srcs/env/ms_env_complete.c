/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_complete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 03:00:26 by gcros             #+#    #+#             */
/*   Updated: 2024/06/13 23:45:32 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <unistd.h>
#include "str.h"
#include "ft_printf.h"

static int	set_pwd(t_env **env);
static int	set_exec(t_env **env, char *exec_cmd);

int	ms_env_complete(t_env **env, char *exec_cmd)
{
	t_env	*tmp;

	if (set_pwd(env) == 1)
		return (1);
	if (set_exec(env, exec_cmd) == 1)
		return (1);
	if (ms_env_exist(*env, "OLDPWD") == 0
		&& (ms_parse_env_node("OLDPWD=", &tmp) == 1
			|| ms_env_add(env, tmp) == 1))
		return (ms_env_collapse(&tmp), 1);
	return (0);
}

static int	set_exec(t_env **env, char *exec_cmd)
{
	char	*exec;
	char	*k;
	t_env	*tmp;

	exec = ft_strdup(exec_cmd);
	if (exec == NULL)
		return (1);
	k = ft_strdup("_");
	if (k == NULL)
		return (free(exec), 1);
	tmp = ms_env_new(k, exec);
	if (tmp == NULL)
		return (free(exec), free(k), 1);
	if (ms_env_add(env, tmp) == 1)
		return (ms_env_collapse(&tmp), 1);
	return (0);
}

static int	set_pwd(t_env **env)
{
	char	*pwd;
	char	*k;
	t_env	*tmp;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	k = ft_strdup("PWD");
	if (k == NULL)
		return (free(pwd), 1);
	tmp = ms_env_new(k, pwd);
	if (tmp == NULL)
		return (free(pwd), free(k), 1);
	if (ms_env_add(env, tmp) == 1)
		return (ms_env_collapse(&tmp), 1);
	return (0);
}
