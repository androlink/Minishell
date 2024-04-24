/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:53:13 by gcros             #+#    #+#             */
/*   Updated: 2024/04/24 05:06:15 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "env.h"

int	cd(int ac, char **args, t_env **env);
int	echo(char **args);
int	pwd(int ac, char **av);

#endif