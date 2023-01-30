/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:24:54 by tnam              #+#    #+#             */
/*   Updated: 2023/01/30 20:45:29 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define CHILD 0
# define IN 0
# define OUT 1
# define ERROR -1

# include "./libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>
# include <stdio.h>

typedef struct s_var
{
	int		argc;
	char	**argv;
	char	**envp;
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	pid_t	pid;
	char	*path;
	char	**cmd;
	size_t	cmd_i;
}			t_var;

void	ft_init_value(t_var *var, int argc, char *argv[], char *envp[]);
void	ft_error(void);
void	ft_get_cmd_path(t_var *var);

#endif