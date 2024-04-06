/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:15:41 by gcros             #+#    #+#             */
/*   Updated: 2024/04/06 02:41:54 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"

int	get_node(char *str, t_env **out);
int	get_key(char *str, char **out);
int	get_value(char *str, char **out);

int	ms_env_gen(char **strs, t_env **env)
{
	char	**p;
	t_env	*tmp;

	p = strs;
	while (*p != NULL)
	{
		if (get_node(*p, &tmp) == 1)
			break;
		ms_env_add(env, tmp);
		p++;
	}
	if (*p == NULL)
		return (0);
	ms_env_collapse(env);
	return (0);
}

int	get_node(char *str, t_env **out)
{
	char	*s1;
	char	*s2;
	t_env	*e;

	if (get_key(str, &s1) == 1 || get_value(str, &s2) == 1)
	{
		free(s1);
		free(s2);
		return ((*out = NULL) || 1);
	}
	e = ms_env_new(s1, s2);
	*out = e;
	if (e == NULL)
	{
		free(s1);
		free(s2);
	}
	return (e == NULL);
}

int	get_key(char *str, char **out)
{
	char	*tmp;
	size_t	i;
	
	tmp = ft_strchr(str, '=');
	if (tmp == NULL)
		return ((*out = ft_strdup(str)) == NULL);
	i = tmp - str;
	tmp = malloc(i + 1);
	if (tmp != NULL)
		ft_strlcpy(tmp, str, i + 1);
	*out = tmp;
	return (*out == NULL);
}

int	get_value(char *str, char **out)
{
	str = ft_strchr(str, '=');
	if (str == NULL)
		return ((*out = NULL) || 1);
	str += *str == '=';
	return ((*out = ft_strdup(str)) == NULL);
}
