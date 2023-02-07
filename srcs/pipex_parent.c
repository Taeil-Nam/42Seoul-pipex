/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:25:24 by tnam              #+#    #+#             */
/*   Updated: 2023/02/07 16:51:47 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_parent(t_var *var)
{
	if (var->cmd_i != var->argc - 2)
	{
		if (close(var->pipe_fd[OUT]) == ERROR)
			ft_error();
	}
	if (var->prev_pipe_fd != NONE)
		if (close(var->prev_pipe_fd) == ERROR)
			ft_error();
	var->prev_pipe_fd = var->pipe_fd[IN];
}
