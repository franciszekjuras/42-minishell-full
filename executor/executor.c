/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:13:59 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/01 13:07:26 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <interface/env.h>
#include <interface/line.h>
#include <interface/global.h>
#include "app.h"
#include "childs.h"
#include "envops.h"
#include "exec_data.h"
#include "lineops.h"

void	minish_env_init(t_env *env, char **parent_environ)
{
	env_init(env, parent_environ);
}

void	minish_env_free(t_env env)
{
	env_free(env);
}

int	minish_execute(t_env *env, t_line line)
{
	t_exec_data	*exec_data_arr;
	t_app		app;
	int			retval;

	if (g_sigint_received)
	{
		line_free(line);
		return (0);
	}
	app_init(&app, env, "minish");
	exec_data_arr = exec_data_arr_init(line.size);
	app_exec_arr(&app, exec_data_arr, line);
	free(exec_data_arr);
	retval = childs_wait_until_all_exit(&app.childs);
	if (app.childs.last < 0)
		retval = app.builtin_last_retval;
	app_free(&app);
	line_free(line);
	env->last_exit_status = retval;
	return (retval);
}
