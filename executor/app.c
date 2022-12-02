/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:54:11 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/02 18:51:17 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/libft.h>
#include <interface/env.h>
#include <interface/line.h>
#include "app.h"
#include "app_priv.h"
#include "exec_data.h"
#include "utils.h"

void	app_init(t_app *app, t_env *env, int line_size, const char *name)
{
	app->env = env;
	app->name = ft_strdup(name);
	app->builtin_last_retval = 0;
	childs_init(&app->childs, line_size);
}

void	app_free(t_app *app)
{
	free(app->name);
	childs_free(&app->childs);
}

void	app_exec_line(t_app *app, t_line line)
{
	int			i;
	t_exec_data	*exec_data_arr;

	exec_data_arr = exec_data_arr_init(line.size);
	i = 0;
	while (i < line.size)
	{
		if (app_pipe_exec_data_arr(app, exec_data_arr, i, line.size) == 0)
			app_fill_exec_data(app, &exec_data_arr[i], line.progs[i]);
		app_exec(app, &exec_data_arr[i]);
		exec_data_free(&exec_data_arr[i]);
		++i;
	}
	free(exec_data_arr);
}
