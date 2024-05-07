/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:46:54 by gcros             #+#    #+#             */
/*   Updated: 2024/05/06 23:08:04 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <errno.h>
#include <stdio.h>
#include "put.h"

int		env_error(int err);
void	print_env(t_env *env);

int	env(char **av, t_env *env)
{
	if (av[0] && av[1])
		return (env_error(E2BIG));
	print_env(env);
	return (0);
}

void	print_env(t_env *env)
{
	char	*pr_val;

	if (env == NULL)
		return ;
	if (env->value)
	{
		pr_val = ft_strsjoin((char *[]){env->key, "=", env->value, NULL});
		if (pr_val)
			ft_putendl_fd(pr_val, 1);
		free(pr_val);
	}
	print_env(env->left);
	print_env(env->right);
}

int	env_error(int err)
{
	if (err == E2BIG)
		ft_putstr_fd("mishell: env: too many arguments\n", 2);
	return (1);
}