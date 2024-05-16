/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 02:12:57 by gcros             #+#    #+#             */
/*   Updated: 2024/05/03 04:37:52 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	unset(char **av, t_env **env)
{
	char	**ptr;

	ptr = av;
	while (*++ptr)
		ms_env_remove(env, *ptr);
	return (0);
}