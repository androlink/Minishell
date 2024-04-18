/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:46:11 by gcros             #+#    #+#             */
/*   Updated: 2024/04/18 16:30:15 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "str.h"
#include "put.h"
#include <errno.h>
#include <sys/stat.h>

int	error_handler(int err, int *out_error);

char	*ms_exec_name(char *name, char *path)
{
	char	*full_name;
	int		ret;

	ret = 0;
	if (ft_strchr(name, '/') == NULL)
	{
		if (error_handler(ms_exec_cmd_path(name, path, &full_name), &ret) != 0
			&& full_name == NULL)
			return (NULL);
	}
	else
	{
		full_name = ft_strdup(name);
		if (full_name == NULL)
			if (error_handler(-1, &ret))
				return (NULL);
	}
	return (NULL);
}

int	error_handler(int err, int *out_error)
{
	*out_error = err;
	return (err);
}
