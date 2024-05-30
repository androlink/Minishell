/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:27:06 by gcros             #+#    #+#             */
/*   Updated: 2024/05/30 15:50:55 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
 
int	ms_exit_status(int new_status, int save)
{
	static int	status;

	if (save)
		status = new_status;
	return (status);
}

int	ms_get_status(void)
{
	return (ms_exit_status(0, 0));
}

void	ms_set_status(int new_status)
{
			fprintf(stderr, "==%d==%d\n", new_status, getpid());
	if (WIFEXITED(new_status))
		new_status = WEXITSTATUS(new_status);
	else if (WIFSIGNALED(new_status))
		new_status = WTERMSIG(new_status) + 128;
			fprintf(stderr, "==%d==%d\n", new_status, getpid());


	ms_exit_status(new_status, 1);
}
