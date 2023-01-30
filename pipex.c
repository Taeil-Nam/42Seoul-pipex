/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:54:39 by tnam              #+#    #+#             */
/*   Updated: 2023/01/30 20:45:29 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_open_files(t_var *var)
{
	var->infile_fd = open(var->argv[0], O_RDONLY);
	if (var->infile_fd == ERROR)
		ft_error();
	var->outfile_fd = open(var->argv[4], O_WRONLY | O_CREAT | O_TRUNC | 0644);
	if (var->outfile_fd == ERROR)
		ft_error();
}

void	ft_child(t_var *var)
{
	if (dup2(var->pipe_fd[OUT], STDOUT_FILENO) == ERROR)
		ft_error();
	if (close(var->pipe_fd[IN]) == ERROR)
		ft_error();
	if (close(var->pipe_fd[OUT]) == ERROR)
		ft_error();
	ft_get_cmd_path(&var);
	if (execve(var->path, var->cmd, var->envp) == ERROR)
		ft_error();
}

// void ft_parent(t_var *var)
// {

// }

int	main(int argc, char *argv[], char *envp[])
{
	t_var	var;

	if (argc != 5)
		return (1);
	ft_init_value(&var, argc, argv, envp);
	ft_open_files(&var);
	if (pipe(var.pipe_fd) == ERROR)
		ft_error();
	if (dup2(var.infile_fd, STDIN_FILENO) == ERROR)
		ft_error();
	var.pid = fork();
	if (var.pid == ERROR)
		ft_error();
	else if (var.pid == CHILD)
		ft_child(&var);
	wait(NULL);
	ft_parent(&var);

	return (0);
}
