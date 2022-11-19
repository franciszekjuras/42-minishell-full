/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_priv2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:54:11 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/07 14:42:41 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <interface/line.h>
#include <libft/libft.h>
#include "builtins.h"
#include "exec_data.h"
#include "app_priv.h"
#include "app.h"

static int	fill_redirs(t_app *app, t_exec_data *exec_data, t_prog prog)
{
	if (prog.in_redir.path != NULL)
		exec_data->fd_in = app_open(app, exec_data, prog.in_redir.path,
				APP_OPEN_IN);
	if (exec_data->fd_in < 0)
		return (-1);
	if (prog.out_redir.path != NULL)
		exec_data->fd_out = app_open(app, exec_data, prog.out_redir.path,
				APP_OPEN_OUT);
	if (exec_data->fd_out < 0)
		return (-1);
	return (0);
}

void	app_fill_exec_data(t_app *app, t_exec_data *exec_data, t_prog prog)
{
	if (fill_redirs(app, exec_data, prog) < 0)
		return ;
	exec_data->args = prog.args;
	exec_data->builtin_fun = builtin_resolve(exec_data->args[0]);
	if (exec_data->builtin_fun != NULL)
	{
		exec_data->is_builtin = 1;
		exec_data->ready = 1;
		return ;
	}
	exec_data->prog_path = app_resolve_prog_path(app, exec_data->args[0]);
	if (exec_data->prog_path != NULL)
		exec_data->ready = 1;
}

int	app_pipe_exec_data_arr(t_app *app,
	t_exec_data *exec_data_arr, int i, int size)
{
	(void)app;
	if (i == 0)
		exec_data_arr[i].fd_in = 0;
	if (i + 1 == size)
	{
		exec_data_arr[i].fd_out = 1;
		return (0);
	}
	else
		return (app_pipe(app, &exec_data_arr[i], &exec_data_arr[i + 1]));
}

void	app_exec(t_app *app, t_exec_data *exec_data)
{
	pid_t		child;

	if (!exec_data->ready || exec_data->is_builtin)
	{
		if (!exec_data->ready)
			app->builtin_last_retval = errno;
		else
			app_exec_builtin(app, exec_data);
		childs_update(&app->childs, -1);
		return ;
	}
	child = fork();
	if (child == 0)
		app_exec_child_side(app, exec_data);
	if (child < 0)
	{
		app->builtin_last_retval = errno;
		ft_dprintf(2, "%s: %s: %s\n", app->name, "fork", strerror(errno));
	}
	childs_update(&app->childs, child);
}
