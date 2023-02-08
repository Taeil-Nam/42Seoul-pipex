/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_awk_sed_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:31:38 by tnam              #+#    #+#             */
/*   Updated: 2023/02/08 17:17:10 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	ft_copycmd(t_parser *p_var)
{
	int		i;
	char	*str;

	str = (char *)malloc(sizeof(char) * p_var->str_len + 1);
	if (str == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (p_var->start <= p_var->end)
	{
		str[i] = p_var->cmd[p_var->start];
		i++;
		p_var->start++;
	}
	str[i] = '\0';
	p_var->result[p_var->str_i++] = str;
}

static void	ft_space(t_parser *p_var)
{
	p_var->end = p_var->i - 1;
	p_var->str_len = (p_var->end - p_var->start) + 1;
	ft_copycmd(p_var);
	while (p_var->cmd[p_var->start] == ' ')
		p_var->start++;
	p_var->i = p_var->start - 1;
}

static void	ft_quote(t_parser *p_var, char quote)
{
	int		quote_end;

	p_var->start = p_var->i + 1;
	quote_end = p_var->start;
	while (!p_var->cmd[quote_end] || p_var->cmd[quote_end] != quote)
		quote_end++;
	p_var->end = quote_end - 1;
	p_var->str_len = (p_var->end - p_var->start) + 1;
	ft_copycmd(p_var);
	p_var->start++;
	while (p_var->cmd[p_var->start] == ' ')
		p_var->start++;
	p_var->i = p_var->start - 1;
}

static void	ft_make_cmd_for_awk_sed(t_var *var, t_parser *p_var)
{
	p_var->result = (char **)malloc(sizeof(char *) * (p_var->str_count + 1));
	if (p_var->result == NULL)
		exit(EXIT_FAILURE);
	while (p_var->cmd[p_var->i])
	{
		if (p_var->cmd[p_var->i] == ' ')
			ft_space(p_var);
		else if (p_var->cmd[p_var->i] == '\'' || p_var->cmd[p_var->i] == '"')
			ft_quote(p_var, p_var->cmd[p_var->i]);
		p_var->i++;
	}
	p_var->result[p_var->str_i] = NULL;
	var->cmd = p_var->result;
	p_var->result = NULL;
}

void	ft_make_cmd_if_awk_sed(t_var *var)
{
	t_parser	p_var;
	int			i;

	if (ft_strncmp(var->cmd[0], "awk", 3) == 0
		|| ft_strncmp(var->cmd[0], "sed", 3) == 0)
	{
		free(var->cmd);
		var->cmd = NULL;
		p_var.i = 0;
		p_var.start = 0;
		p_var.end = 0;
		p_var.str_i = 0;
		p_var.str_count = 1;
		p_var.str_len = 0;
		p_var.cmd = var->argv[var->cmd_i];
		p_var.result = NULL;
		i = 0;
		while (p_var.cmd[i])
		{
			if (p_var.cmd[i] == ' ')
				p_var.str_count++;
			i++;
		}
		ft_make_cmd_for_awk_sed(var, &p_var);
	}
}
