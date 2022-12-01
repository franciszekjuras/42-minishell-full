/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:03:37 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/01 15:39:44 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <libft/libft.h>
#include "childs.h"

void	childs_init(t_childs *childs, int max_num)
{
	childs->number = 0;
	childs->last = -1;
	childs->arr = ft_calloc(max_num, sizeof(pid_t));
}

void	childs_free(t_childs *childs)
{
	free(childs->arr);
}

void	childs_update(t_childs *childs, pid_t child)
{
	if (child >= 0)
	{
		childs->arr[childs->number] = child;
		childs->number++;
	}
	childs->last = child;
}
