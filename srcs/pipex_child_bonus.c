/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:25:31 by tnam              #+#    #+#             */
/*   Updated: 2023/02/06 12:09:17 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	ft_first_cmd(t_var *var)
{
	var->infile_fd = open(var->argv[1], O_RDONLY);
	if (var->infile_fd == ERROR)
		ft_error();
	if (dup2(var->infile_fd, 0) == ERROR)
		ft_error();
	if (dup2(var->pipe_fd[1], 1) == ERROR)
		ft_error();
	if (close(var->infile_fd) == ERROR)
		ft_error();
	if (close(var->pipe_fd[0]) == ERROR)
		ft_error();
	if (close(var->pipe_fd[1]) == ERROR)
		ft_error();
	ft_find_cmd_path(var);
	if (execve(var->cmd_path, var->cmd, var->envp) == ERROR)
		ft_error();
}

static void	ft_middle_cmd(t_var *var)
{
	if (dup2(var->prev_pipe_fd, 0) == ERROR)
		ft_error();
	if (dup2(var->pipe_fd[1], 1) == ERROR)
		ft_error();
	if (close(var->prev_pipe_fd) == ERROR)
		ft_error();
	if (close(var->pipe_fd[0]) == ERROR)
		ft_error();
	if (close(var->pipe_fd[1]) == ERROR)
		ft_error();
	ft_find_cmd_path(var);
	if (execve(var->cmd_path, var->cmd, var->envp) == ERROR)
		ft_error();
}

static void	ft_last_cmd(t_var *var)
{
	var->outfile_fd = open(var->argv[var->argc - 1], O_WRONLY
			| O_CREAT | O_TRUNC | 0644);
	if (var->outfile_fd == ERROR)
		ft_error();
	if (dup2(var->prev_pipe_fd, 0) == ERROR)
		ft_error();
	if (dup2(var->outfile_fd, 1) == ERROR)
		ft_error();
	if (close(var->prev_pipe_fd) == ERROR)
		ft_error();
	if (close(var->outfile_fd) == ERROR)
		ft_error();
	ft_find_cmd_path(var);
	if (execve(var->cmd_path, var->cmd, var->envp) == ERROR)
		ft_error();
}

// static void	ft_here_doc_cmd(t_var *var)
// {
	// To do
	// - here_doc 전용 로직
// }

void	ft_child(t_var *var)
{
	if (var->here_doc)
		ft_here_doc_cmd(var);
	if (var->cmd_i == 2)
		ft_first_cmd(var);
	else if (var->cmd_i == var->argc - 2)
		ft_last_cmd(var);
	else
		ft_middle_cmd(var);
}
