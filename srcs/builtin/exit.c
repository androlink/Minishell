/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:55:46 by gcros             #+#    #+#             */
/*   Updated: 2024/06/21 18:39:40 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "exec.h"
#include "put.h"
#include "num.h"

int	def_exit(t_exec *exec, t_shell *shell);
int	arg_exit(t_exec *exec, t_shell *shell);

int	b_exit(t_exec *exec, t_shell *shell)
{
	if (exec->content->size == 1)
		return (def_exit(exec, shell));
	else
		return (arg_exit(exec, shell));
	return (EXIT_FAILURE << 8);
}

int	exit_error(int err, char *op)
{
	char	*err_msg;

	err_msg = NULL;
	if (err == 0)
		err_msg = ft_strsjoin((char *[])
			{"mishell: exit: too many argument", NULL});
	else if (err == 1)
		err_msg = ft_strsjoin((char *[])
			{"mishell: exit: ", op, ": bad arguments", NULL});
	else
		err_msg = ft_strdup("mishell: exit: good luck");
	if (err_msg)
		ft_putendl_fd(err_msg, 2);
	free(err_msg);
	return (err);
}

int	def_exit(t_exec *exec, t_shell *shell)
{
	free_shell(shell);
	free_exec(exec);
	close_all();
	exit(ms_get_status());
}

int	arg_exit(t_exec *exec, t_shell *shell)
{
	int	st;

	st = ft_atol(exec->content->data[1]);
	if (!ft_strisnumber(exec->content->data[1])
		|| ((char *)exec->content->data[1])[0] == '\0')
	{
		if (exit_error(1, exec->content->data[1]) == 1)
			st = 2;
	}
	else if (exec->content->size > 2)
	{
		if (exit_error(0, NULL) == 0)
			return (1 << 8);
	}
	free_shell(shell);
	free_exec(exec);
	close_all();
	exit(st);
}
