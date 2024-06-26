/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_get_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 05:00:59 by gcros             #+#    #+#             */
/*   Updated: 2024/06/14 17:46:11 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "put.h"
#include "conf.h"

int		check_file(char *path, char *name, char **out);
int		ms_find_cmd(char *cmd, char *env_path, char **out);
int		check_bin(char *bin, char *cmd);
void	set_exit(char *bin, char *cmd);

char	*get_bin(char *cmd, t_env *env)
{
	char	*bin;

	if (ft_strchr(cmd, '/') == NULL)
		ms_find_cmd(cmd, ms_env_get(env, "PATH"), &bin);
	else
		bin = ft_strdup(cmd);
	set_exit(bin, cmd);
	if (check_bin(bin, cmd) == 0)
		ft_nfree((void **)&bin);
	return (bin);
}

void	set_exit(char *bin, char *cmd)
{
	int			st;
	const int	is_cmd = !ft_strchr(cmd, '/');

	st = fs_default;
	if (bin)
		st = get_file_status(bin);
	if (!(st & fs_exist) && is_cmd)
		ms_set_status(127);
	else if (!(st & fs_exist) && !is_cmd)
		ms_set_status(127);
	else if (st & fs_is_dir)
		ms_set_status(126 << 8);
	else if (!((st & (fs_exec | fs_read)) == (fs_exec | fs_read)))
		ms_set_status(126 << 8);
}

int	check_bin(char *bin, char *cmd)
{
	int			st;
	const int	is_cmd = !ft_strchr(cmd, '/');
	char		*err_msg;

	err_msg = NULL;
	st = fs_default;
	if (bin)
		st = get_file_status(bin);
	if ((st & fs_exist) == 0 && is_cmd)
		err_msg = ft_strsjoin((char *[]){cmd, ": command not found", NULL});
	else if ((st & fs_exist) == 0 && !is_cmd)
		err_msg = ft_strsjoin((char *[])
			{MS_NAME": ", bin, ": No such file or directory", NULL});
	else if (st & fs_is_dir)
		err_msg = ft_strsjoin((char *[])
			{MS_NAME": ", bin, ": Is a directory", NULL});
	else if (!((st & (fs_exec | fs_read)) == (fs_exec | fs_read)))
		err_msg = ft_strsjoin((char *[])
			{MS_NAME": ", bin, ": Permission denied", NULL});
	if (err_msg)
		ft_putendl_fd(err_msg, 2);
	free(err_msg);
	return (((st | fs_read | fs_write)
			^ (fs_exist | !fs_is_dir | fs_read | fs_write | fs_exec)) == 0);
}

int	ms_find_cmd(char *cmd, char *env_path, char **out)
{
	char	**paths;
	char	**ptr;
	int		ret;

	*out = NULL;
	ret = 0;
	if (env_path == NULL || ft_strlen(env_path) == 0)
		return (check_file(".", cmd, out));
	if (cmd == NULL || *cmd == '\0')
		return (1);
	paths = ft_split(env_path, ':');
	if (paths == NULL)
		return (0);
	ptr = paths - 1;
	while (*++ptr != NULL)
	{
		ret = check_file(*ptr, cmd, out);
		if (ret)
			break ;
	}
	ft_strsfree(paths);
	return (ret);
}

int	check_file(char *path, char *name, char **out)
{
	char	*file;
	int		r;

	file = ft_strsjoin((char *[]){path, "/", name, NULL});
	if (file == NULL)
		return (0);
	r = get_file_status(file);
	if (!(r & fs_exist))
		return (free(file), 0);
	if (r & fs_exec)
		free(*out);
	*out = file;
	return (r & fs_exec);
}
