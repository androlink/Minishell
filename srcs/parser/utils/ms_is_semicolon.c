/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:39 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:44:43 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "parser.h"

int	ms_is_semicolon(t_type type, char *line)
{
	if (type == E_METACHAR && ft_strncmp(line, ";", 1) == 0)
		return (1);
	return (0);
}
