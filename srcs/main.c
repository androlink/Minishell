/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:37:28 by gcros             #+#    #+#             */
/*   Updated: 2024/04/06 02:45:51 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;

	t_env	*e;

	e = NULL;
	printf("%p", *env);
	printf("%d\n", ms_env_gen(env, &e));
	printf("%s\n", ms_env_get(e, "test"));
	ms_env_collapse(&e);

	return (0);
}
