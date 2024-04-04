/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:10:36 by androlink         #+#    #+#             */
/*   Updated: 2024/03/28 03:52:11 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr.h"

int	ft_arr_resize(t_array *array, size_t ncapacity)
{
	void	**data;

	if (ncapacity < array->size)
		return (0);
	data = (void **)ft_calloc(sizeof(void *), ncapacity);
	if (data == NULL)
		return (0);
	ft_memcpy(data, array->data, array->size * sizeof(void *));
	free(array->data);
	array->data = data;
	array->capacity = ncapacity;
	return (1);
}
