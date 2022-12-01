/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:13:59 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/01 14:43:34 by fjuras           ###   ########.fr       */
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
	t_app		app;
	int			retval;

	app_init(&app, env, line.size, "minish");
	app_exec_line(&app, line);
	retval = childs_wait_until_all_exit(&app.childs);
	if (app.childs.last < 0)
		retval = app.builtin_last_retval;
	app_free(&app);
	line_free(line);
	env->last_exit_status = retval;
	return (retval);
}
