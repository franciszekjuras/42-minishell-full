/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:51:27 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/27 19:58:40 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_line translate(t_cmd *cmd)
{
    int     idx;
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
        line.progs[idx].args = ft_calloc(cur_cmd->argc + 1, sizeof(char *));
        for (int i = 0; i < cur_cmd->argc; i++)
        {
            line.progs[idx].args[i] = ft_strdup(cur_cmd->argv[i]);
        }
        idx++;
        cur_cmd = cur_cmd->next;
    }

    return (line);
}
