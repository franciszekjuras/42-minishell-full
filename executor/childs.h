/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:03:31 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/01 15:39:51 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILDS_H
# define CHILDS_H

# include <sys/types.h>

typedef struct s_childs
{
	int		number;
	pid_t	last;
	pid_t	*arr;
}	t_childs;

void	childs_init(t_childs *childs, int max_num);
void	childs_free(t_childs *childs);
void	childs_update(t_childs *childs, pid_t child);
int		childs_wait_until_all_exit(t_childs *childs);

#endif