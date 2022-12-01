/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:03:37 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/01 18:11:43 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <interface/global.h>
#include <libft/libft.h>
#include "childs.h"

static int	get_retval_from_exit_status(int exit_status)
{
	if (!WIFSIGNALED(exit_status))
		return (WEXITSTATUS(exit_status));
	else
		return (128 + WTERMSIG(exit_status));
}


static void	childs_remove(t_childs *childs, pid_t child)
{
	int	i;

	if (child >= 0)
	{
		i = 0;
		while (i < childs->number)
		{
			if (childs->arr[i] == child)
			{
				childs->arr[i] = -1;
				return ;
			}
			++i;
		}
	}
}

static void	childs_sigint_all(t_childs *childs)
{
	int	i;

	i = 0;
	while (i < childs->number)
	{
		if (childs->arr[i] >= 0)
			kill(childs->arr[i], SIGINT);
		++i;
	}
}

int	childs_wait_until_all_exit(t_childs *childs)
{
	int		i;
	int		retval;
	int		exited_status;
	pid_t	exited_pid;

	retval = 0;
	i = 0;
	while (i < childs->number)
	{
		exited_pid = wait(&exited_status);
		childs_remove(childs, exited_pid);
		if (exited_pid == childs->last && childs->last >= 0)
			retval = get_retval_from_exit_status(exited_status);
		if (g_shell_state == SHELL_STATE_INTPT)
		{
			childs_sigint_all(childs);
			g_shell_state = SHELL_STATE_EXEC;
		}
		if (exited_pid >= 0)
			++i;
	}
	return (retval);
}
