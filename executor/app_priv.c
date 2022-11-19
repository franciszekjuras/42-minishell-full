/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_priv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:22:54 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/19 17:31:33 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libft/libft.h>
#include "app.h"
#include "exec_data.h"
#include "utils.h"

char	*app_resolve_prog_path(t_app *app, char *prog)
{
	char	*candidate;
	char	**path;

	if (ft_strchr(prog, '/') != NULL)
		return (ft_strdup(prog));
	candidate = NULL;
	path = app->env->path;
	while (*path != NULL)
	{
		if (check_if_path_is_executable(*path, prog, &candidate))
			break ;
		++path;
	}
	if (candidate == NULL)
		ft_dprintf(2, "%s: %s: %s\n", app->name, prog, "command not found");
	return (candidate);
}

void	app_exec_child_side(t_app *app, t_exec_data *exec_data)
{
	dup2(exec_data->fd_in, STDIN_FILENO);
	dup2(exec_data->fd_out, STDOUT_FILENO);
	exec_data_close_tracked_fds(exec_data);
	if (exec_data->pipe_next_fd >= 0)
		close(exec_data->pipe_next_fd);
	execve(exec_data->prog_path, exec_data->args, app->env->vars);
	ft_dprintf(2, "%s: %s: %s\n", app->name,
		exec_data->args[0], strerror(errno));
	exec_data_free(exec_data);
	app_free(app);
	exit(errno);
}

void	app_exec_builtin(t_app *app, t_exec_data *exec_data)
{
	app->builtin_last_retval = exec_data->builtin_fun(app, exec_data);
}

int	app_pipe(t_app *app,
	t_exec_data *exec_data_in, t_exec_data *exec_data_out)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == 0)
	{
		exec_data_track_fd(exec_data_in, pipe_fds[1]);
		exec_data_in->fd_out = pipe_fds[1];
		exec_data_in->pipe_next_fd = pipe_fds[0];
		exec_data_track_fd(exec_data_out, pipe_fds[0]);
		exec_data_out->fd_in = pipe_fds[0];
		return (0);
	}
	else
	{
		ft_dprintf(2, "%s: %s: %s\n", app->name, "pipe", strerror(errno));
		return (-1);
	}
}

int	app_open(t_app *app, t_exec_data *exec_data, char *file, int mode)
{
	int	fd;

	fd = -1;
	if (mode == APP_OPEN_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == APP_OPEN_IN || 1)
		fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: %s\n", app->name, file, strerror(errno));
		return (-1);
	}
	exec_data_track_fd(exec_data, fd);
	return (fd);
}
