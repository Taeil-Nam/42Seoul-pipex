/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:46:17 by tnam              #+#    #+#             */
/*   Updated: 2023/02/08 16:35:20 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	ft_here_doc_get_input(t_var *var)
{
	char	*input;
	int		temp_fd;

	temp_fd = open("temp", O_WRONLY | O_CREAT
			| O_TRUNC | O_APPEND, 0644);
	if (temp_fd == ERROR)
		ft_error();
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		input = get_next_line(STDIN_FILENO);
		if (!input
			||ft_strncmp(input, var->limiter, ft_strlen(var->limiter)) == 0)
			break ;
		write(temp_fd, input, ft_strlen(input));
		free(input);
	}
	free(input);
	if (close(temp_fd) == ERROR)
		ft_error();
}

void	ft_here_doc_first_cmd(t_var *var)
{
	ft_here_doc_get_input(var);
	var->infile_fd = open("temp", O_RDONLY);
	if (var->infile_fd == ERROR)
		ft_error();
	if (dup2(var->infile_fd, STDIN_FILENO) == ERROR)
		ft_error();
	if (dup2(var->pipe_fd[OUT], STDOUT_FILENO) == ERROR)
		ft_error();
	if (close(var->infile_fd) == ERROR)
		ft_error();
	if (close(var->pipe_fd[IN]) == ERROR)
		ft_error();
	if (close(var->pipe_fd[OUT]) == ERROR)
		ft_error();
	if (execve(var->cmd_path, var->cmd, var->envp) == ERROR)
		ft_error();
}

void	ft_here_doc_last_cmd(t_var *var)
{
	var->outfile_fd = open(var->argv[var->argc - 1], O_WRONLY
			| O_CREAT | O_APPEND, 0644);
	if (var->outfile_fd == ERROR)
		ft_error();
	if (dup2(var->prev_pipe_fd, STDIN_FILENO) == ERROR)
		ft_error();
	if (dup2(var->outfile_fd, STDOUT_FILENO) == ERROR)
		ft_error();
	if (close(var->prev_pipe_fd) == ERROR)
		ft_error();
	if (close(var->outfile_fd) == ERROR)
		ft_error();
	if (execve(var->cmd_path, var->cmd, var->envp) == ERROR)
		ft_error();
}
