/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:37:28 by gcros             #+#    #+#             */
/*   Updated: 2024/05/03 00:44:51 by gcros            ###   ########.fr       */
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
/**
 * @file main.c
 * @brief Fichier principale du programme qui va initialiser la structure shell et lancer le prompt
 * 
 */
 
#include "minishell.h"
#include "prompt.h"

/**
 * @brief Fonction principale du programme qui va initialiser la structure shell et lancer le prompt
 * 
 * @param argc **Non Utilisé** (Argument Count) Contient le nombre d'arguments passés au programme
 * @param argv **Non Utilisé** (Argument Vector) Contient les arguments passés au programme
 * @param envp Variable d'**environnement** qui seront **dupliqué** et **stocké** dans la **structure shell**
 * @return int **0** si tout c'est bien passé sinon **1**
 */
int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;

	t_shell	*shell;
	shell = malloc(sizeof(t_shell) * 1);
	ms_env_gen(envp, &(shell->env));
	if (!shell)
		return (1);

	ms_prompt(shell);

	return (0);
}
