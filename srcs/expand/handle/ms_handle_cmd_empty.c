/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd_empty.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 06:40:22 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/11 16:27:34 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "wildcard.h"
#include "expand.h"
#include "put.h"
#include "conf.h"

static void	apply_wildcard(t_array *new_array)
{
	t_array		*tmp_array;
	t_command	*command;
	char		*tmp_str;

	command = ft_arr_pop(new_array);
	tmp_array = ms_pathexp(command->content.str);
	free(command->content.str);
	free(command);
	if (tmp_array == NULL)
		return ;
	if (tmp_array->size > 1 &&
		(ms_get_before_type_widlcard(new_array) == CMD_REDIR_IN
			|| ms_get_before_type_widlcard(new_array) == CMD_REDIR_OUT
			|| ms_get_before_type_widlcard(new_array) == CMD_APPEND))
		ft_putendl_fd(MS_NAME ": ambiguous redirect", 2);
	while (tmp_array->size > 0)
	{
		tmp_str = ft_arr_shift(tmp_array);
		ms_append_new_command_str(new_array, CMD_TEXT, tmp_str);
		free(tmp_str);
		ms_append_new_command_str(new_array, CMD_EMPTY, NULL);
	}
	ft_arr_free(&tmp_array, NULL);
	return ;
}

void	ms_handle_cmd_empty(t_array *new_array)
{
	if (ms_get_last_type(new_array) == CMD_WILDCARD)
		apply_wildcard(new_array);
	else
		ms_append_new_command_str(new_array, CMD_EMPTY, NULL);
}