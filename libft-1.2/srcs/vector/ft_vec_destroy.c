/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:55:27 by gcros             #+#    #+#             */
/*   Updated: 2024/02/07 05:03:01 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdlib.h>

void	ft_vec_destroy(t_vector *vector)
{
	free(vector->data);
}

void	ft_vec_free(t_vector **vector)
{
	ft_vec_destroy(*vector);
	free(*vector);
	*vector = NULL;
}
