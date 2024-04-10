/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_to_strs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:18:27 by gcros             #+#    #+#             */
/*   Updated: 2024/04/10 18:16:38 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "arr.h"
#include "str.h"

int	ms_get_strs(t_env *env, t_array *arr);

int	ms_env_to_strs(t_env *env, char ***out)
{
	t_array	*arr;

	arr = ft_arr_new(10);
	if (arr == NULL)
		return ((*out = NULL) || 1);
	if (ms_get_strs(env, arr) == 1 || ft_arr_append(arr, NULL) == 0)
	{
		ft_arr_free(&arr, &free);
		return ((*out = NULL) || 1);
	}
	*out = (char **)arr->data;
	free(arr);
	return (0);
}

int	ms_get_strs(t_env *env, t_array *arr)
{
	char	*str;

	if (env == NULL)
		return (0);
	str = ft_strsjoin((char *[4]){env->key, "=", env->value, NULL});
	if (str == NULL)
		return (1);
	if (ft_arr_append(arr, str) == 0)
		return (free(str), 1);
	return (ms_get_strs(env->left, arr) == 1
		|| ms_get_strs(env->right, arr) == 1);
}
