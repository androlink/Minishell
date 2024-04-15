/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:37:28 by gcros             #+#    #+#             */
/*   Updated: 2024/04/10 21:31:26 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "ft_printf.h"
//#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;

	t_env	*e;
	char	**strs;
	char	**ptr;

	e = NULL;
	ft_printf("%d\n", ms_env_gen(env, &e));
	ft_printf("%d\n", ms_env_complete(&e, av[0]));
	if (ms_env_to_strs(e, &strs) == 1)
	{
		write(2, "lol\n", 4);
		return (1);
	}
	ms_env_collapse(&e);
	ptr = strs;
	while (*ptr)
	{
		ft_printf("%s\n", *ptr);
		ptr++;
	}
	ft_strsfree(strs);
	return (0);
}
