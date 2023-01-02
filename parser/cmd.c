/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:00:29 by chan-hpa          #+#    #+#             */
/*   Updated: 2023/01/02 21:34:00 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

void	*ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
	}
	return (NULL);
}

t_cmd	*ft_list_init(void)
{
	t_cmd	*new_mem;

	new_mem = malloc(sizeof(t_cmd));
	new_mem->argc = 0;
	new_mem->argv = NULL;
	new_mem->is_dollar = false;
	new_mem->infile = -2;
	new_mem->outfile = -2;
	new_mem->cmd_path = NULL;
	new_mem->is_pipe = false;
	new_mem->next = NULL;
	new_mem->prev = NULL;
	return (new_mem);
}

void	ft_free_list(t_cmd *cmd)
{
	t_cmd	*ptr;
	int		i;

	while (cmd->prev != NULL)
		cmd = cmd->prev;
	while (cmd)
	{
		i = 0;
		while (i < cmd->argc)
		{
			cmd->argv[i] = ft_free(cmd->argv[i]);
			i++;
		}
		cmd->argv = ft_free(cmd->argv);
		ptr = cmd;
		cmd = cmd->next;
		ptr = ft_free(ptr);
	}
}
