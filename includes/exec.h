/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:50:41 by gcros             #+#    #+#             */
/*   Updated: 2024/04/17 17:08:03 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

int	ms_exec_cmd_path(char *name, char *path, char **out);
int	is_file(char *path);
int	is_exec(char *path);
int	can_read(char *path);
int	can_write(char *path);

#endif