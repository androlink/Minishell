/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_find_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:48:28 by gcros             #+#    #+#             */
/*   Updated: 2024/04/16 04:04:33 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include <unistd.h>

int	can_access(char *path, char *name);

int	ms_get_binary_path(char *name, char *path, char **out)
{
	char	**paths;
	char	**ptr;

	if (path == NULL)
		return ((*out = NULL) && 0);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return ((*out = NULL) && 0);
	ptr = paths;
	while (*ptr != NULL)
	{
		if (can_access(*ptr, name) == 1)
			break ;
		ptr++;
	}
	if (*ptr == NULL)
		return (ft_strsfree(paths), (*out = NULL) && 0);
	*out = ft_strsjoin((char *[]){*ptr, "/", name, NULL});
	ft_strsfree(paths);
	return (*out != NULL);
}

int	can_access(char *path, char *name)
{
	char	*file;
	int		ret;

	file = ft_strsjoin((char *[]){path, "/", name, NULL});
	if (file == NULL)
		return (-1);
	ret = access(file, X_OK);
	free(file);
	return (ret == 0);
}
