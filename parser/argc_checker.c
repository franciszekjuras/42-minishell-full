/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argc_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:57:20 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/18 20:12:53 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	first(t_cmd *tmp, t_cmd **ptr, t_cmd **head)
{
	tmp = (*ptr)->next;
	tmp->prev = NULL;
	(*head)->argv = ft_free((*head)->argv);
	*head = ft_free((*head));
	*head = tmp;
	*ptr = tmp;
}

//TODO: why do we check argc values? Either write a testcase for it or remove it
void	argc_checker(t_cmd **cmd)
{
	t_cmd	*ptr;
	t_cmd	*tmp;

	tmp = NULL;
	ptr = *cmd;
	while (ptr)
	{
		if (ptr->prev == NULL && ptr->next == NULL)
			return ;
		if (ptr->argc == 0 && ptr->prev == NULL)
			first(tmp, &ptr, cmd);
		else if (ptr->argc == 0)
		{
			tmp = ptr->prev;
			tmp->next = ptr->next;
			ptr->argv = ft_free(ptr->argv);
			ptr = ft_free(ptr);
			ptr = tmp->next;
			if (ptr)
				ptr->prev = tmp;
		}
		else
			ptr = ptr->next;
	}
}
