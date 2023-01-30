/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:44:36 by tnam              #+#    #+#             */
/*   Updated: 2023/01/30 21:18:41 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_value(t_var *var, int argc, char *argv[], char *envp[])
{
	var->argc = argc;
	var->argv = argv;
	var->envp = envp;
	var->path = NULL;
	var->cmd = NULL;
	var->cmd_i = 2;
}

void	ft_error(void)
{
	perror(NULL);
	exit(errno);
}

// void	ft_get_cmd_path(t_var *var)
// {

// 	var->cmd_i += 1;
// }
