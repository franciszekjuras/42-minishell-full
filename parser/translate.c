/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:51:27 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/27 15:26:28 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_line translate(t_cmd *cmd)
{
    int     idx;
    t_cmd	*ptr_cmd;
    // This style of naming variables (ptr_ prefix) is called 'Hungarian Notation'
    // and is generally considered bad practice nowadays, e.g. see this post
    // https://stackoverflow.com/questions/111933/why-shouldnt-i-use-hungarian-notation
    // I advice to avoid it if you don't have a very good reason
    t_line	ptr_line;

    idx = 0;
    ptr_cmd = cmd;
    while (ptr_cmd)
    {
        idx++;
        ptr_cmd = ptr_cmd->next;
    }
    ptr_line.size = idx;
    // (t_prog *) cast is unnecessary
    ptr_line.progs = (t_prog *)malloc(sizeof(t_prog) * ptr_line.size);
    idx = 0;
    ptr_cmd = cmd;
    while (ptr_cmd)
    {
        for (int i = 0; i < ptr_cmd->argc; i++)
        {
            ptr_line.progs[idx].args[i] =  ft_strdup(ptr_cmd->argv[i]);
            printf("%s\n", ptr_line.progs[idx].args[i]);
        }
        idx++;
        ptr_cmd = ptr_cmd->next;
    }

    return (ptr_line);
}