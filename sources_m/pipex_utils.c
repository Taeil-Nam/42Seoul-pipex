/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:44:36 by tnam              #+#    #+#             */
/*   Updated: 2023/02/03 17:25:33 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(void)
{
	perror(NULL);
	exit(errno);
}

static char	*ft_make_cmd_path(t_var *var, char *path)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (temp == NULL)
		exit(1);
	result = ft_strjoin(temp, var->cmd[0]);
	if (result == NULL)
	{
		free(temp);
		exit(1);
	}
	free(temp);
	return (result);
}

void	ft_find_cmd_path(t_var *var)
{
	size_t	i;
	char	*cmd_path;

	var->cmd = ft_split(var->argv[var->cmd_i], ' ');
	i = 0;
	while (var->paths[i])
	{
		cmd_path = ft_make_cmd_path(var, var->paths[i]);
		if (access(cmd_path, X_OK) == 0)
		{
			var->cmd_path = cmd_path;
			var->cmd_isin = 1;
			free(cmd_path);
			break ;
		}
		free(cmd_path);
		i++;
	}
	if (var->cmd_isin == -1)
	{
		write(1, "command not found: ", 19);
		write(1, var->cmd[0], ft_strlen(var->cmd[0]));
		write(1, "\n", 1);
		exit(127);
	}
}
