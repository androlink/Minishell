/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:37:28 by gcros             #+#    #+#             */
/*   Updated: 2024/04/26 06:44:49 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "ft_printf.h"
//#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"

int	main(int ac, char **av, char **envs)
{
	t_env	*envp;

	(void) ac;
	(void) av;
	(void) envs;
	envp = NULL;
	ms_env_gen(envs, &envp);
	unset(ac, av, &envp);
	env(1, (char *[]){"env", NULL}, envp);
	ms_env_collapse(&envp);
	return (0);
}