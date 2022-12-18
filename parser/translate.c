/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:51:27 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/15 22:49:20 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_line	translate(t_cmd *cmd)
{
	int		idx;
	t_cmd	*cur_cmd;
	t_line	line;

	idx = 0;
	cur_cmd = cmd;
	while (cur_cmd)
	{
		idx++;
		cur_cmd = cur_cmd->next;
	}
	line.size = idx;
	line.progs = ft_calloc(line.size, sizeof(t_prog));
	idx = 0;
	cur_cmd = cmd;
	while (cur_cmd)
	{
		line.progs[idx].in_redir.path = NULL;
		line.progs[idx].out_redir.path = NULL;
		line.progs[idx].args = ft_calloc(cur_cmd->argc + 1, sizeof(char *));
		for (int i = 0, j = 0; i < cur_cmd->argc; i++)
		{
			if (ft_strcmp(cur_cmd->argv[i], "<") == 0)
			{
				line.progs[idx].in_redir.path = ft_strdup(cur_cmd->argv[++i]);
				line.progs[idx].in_redir.is_alt = 0;
				// printf("path: %s\n", line.progs[idx].in_redir.path);
			}
			else if (ft_strcmp(cur_cmd->argv[i], ">") == 0)
			{
				line.progs[idx].out_redir.path = ft_strdup(cur_cmd->argv[++i]);
				line.progs[idx].out_redir.is_alt = 0;
				// printf("path: %s\n", line.progs[idx].out_redir.path);
			}
			else if (ft_strcmp(cur_cmd->argv[i], "<<") == 0)
			{
				line.progs[idx].in_redir.path = ft_strdup(cur_cmd->argv[++i]);
				line.progs[idx].in_redir.is_alt = 1;
				// printf("path: %s\n", line.progs[idx].in_redir.path);
			}
			else if (ft_strcmp(cur_cmd->argv[i], ">>") == 0)
			{
				line.progs[idx].out_redir.path = ft_strdup(cur_cmd->argv[++i]);
				line.progs[idx].out_redir.is_alt = 1;
				// printf("path: %s\n", line.progs[idx].out_redir.path);
			}
			else
			{
				line.progs[idx].args[j++] = ft_strdup(cur_cmd->argv[i]);
			}
			// printf("line: %d %s\n", j, line.progs[idx].args[j]);
		}
		idx++;
		cur_cmd = cur_cmd->next;
	}

	return (line);
}
