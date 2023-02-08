/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_find_cmd_path_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:33:25 by tnam              #+#    #+#             */
/*   Updated: 2023/02/08 16:21:34 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	ft_cmd_not_found_error(t_var *var)
{
	write(1, "command not found: ", 19);
	write(1, var->cmd[0], ft_strlen(var->cmd[0]));
	write(1, "\n", 1);
	exit(127);
}

static int	ft_check_cmd_is_absolute_path(t_var *var)
{
	if (access(var->cmd[0], X_OK) == SUCCESS)
	{
		var->cmd_path = var->cmd[0];
		return (1);
	}
	return (0);
}

static char	*ft_make_path(t_var *var, char *path)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (temp == NULL)
		exit(EXIT_FAILURE);
	result = ft_strjoin(temp, var->cmd[0]);
	if (result == NULL)
	{
		free(temp);
		exit(EXIT_FAILURE);
	}
	free(temp);
	return (result);
}

void	ft_find_cmd_path(t_var *var)
{
	size_t	i;
	char	*cmd_path;

	var->cmd = ft_split(var->argv[var->cmd_i], ' ');
	if (var->cmd == NULL)
		exit(EXIT_FAILURE);
	if (ft_check_cmd_is_absolute_path(var))
		return ;
	i = 0;
	while (var->paths[i])
	{
		cmd_path = ft_make_path(var, var->paths[i]);
		if (access(cmd_path, X_OK) == SUCCESS)
		{
			var->cmd_path = cmd_path;
			var->cmd_isin = 1;
			break ;
		}
		free(cmd_path);
		i++;
	}
	if (var->cmd_isin == 0)
		ft_cmd_not_found_error(var);
}
