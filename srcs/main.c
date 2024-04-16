/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:37:28 by gcros             #+#    #+#             */
/*   Updated: 2024/04/16 04:54:27 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "ft_printf.h"
//#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "exec.h"

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	t_env	*e;
	char	*path;

	e = NULL;
	ft_printf("%d\n", ms_env_gen(env, &e));
	ft_printf("%d\n", ms_env_complete(&e, av[0]));
	path = ms_env_get(e, "PATH");
	ft_printf("PATH = %s\n", path);
	ms_get_binary_path("which", path, &path);
	ft_printf("%s\n", path);
	free(path);
	ms_env_collapse(&e);
	return (0);
}
