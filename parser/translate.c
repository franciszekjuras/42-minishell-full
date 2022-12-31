/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan-hpa <chan-hpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:51:27 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/31 23:32:53 by chan-hpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	ft_translate_init(t_line *line, int idx, int *i, int*j)
{
	line->progs[idx].in_redir.path = NULL;
	line->progs[idx].out_redir.path = NULL;
	*i = 0;
	*j = 0;
}

static int	ft_cmd_len(t_cmd *cur_cmd)
{
	int		len;
	t_cmd	*tmp_cmd;

	len = 0;
	tmp_cmd = cur_cmd;
	while (tmp_cmd)
	{
		len++;
		tmp_cmd = tmp_cmd->next;
	}
	return (len);
}

static int	ft_translate_redir(t_cmd *cur_cmd, t_line *line, int idx, int *i)
{
	int	flag;

	flag = 1;
	if (cur_cmd->argc == 1)
		return (0);
	if (ft_strcmp(cur_cmd->argv[*i], "<") == 0)
		ft_translate_redir_in_0(cur_cmd, line, idx, i);
	else if (ft_strcmp(cur_cmd->argv[*i], ">") == 0)
		ft_translate_redir_out_0(cur_cmd, line, idx, i);
	else if (ft_strcmp(cur_cmd->argv[*i], "<<") == 0)
		ft_translate_redir_in_1(cur_cmd, line, idx, i);
	else if (ft_strcmp(cur_cmd->argv[*i], ">>") == 0)
		ft_translate_redir_out_1(cur_cmd, line, idx, i);
	else
		flag = 0;
	return (flag);
}

t_line	translate(t_cmd *cmd)
{
	int		idx;
	int		i;
	int		j;
	t_cmd	*cur_cmd;
	t_line	line;

	idx = 0;
	cur_cmd = cmd;
	line.size = ft_cmd_len(cur_cmd);
	line.progs = ft_calloc(line.size, sizeof(t_prog));
	while (cur_cmd)
	{
		ft_translate_init(&line, idx, &i, &j);
		line.progs[idx].args = ft_calloc(cur_cmd->argc + 1, sizeof(char *));
		while (i < cur_cmd->argc)
		{
			if (!ft_translate_redir(cur_cmd, &line, idx, &i))
				line.progs[idx].args[j++] = ft_strdup(cur_cmd->argv[i]);
			i++;
		}
		idx++;
		cur_cmd = cur_cmd->next;
	}
	return (line);
}
