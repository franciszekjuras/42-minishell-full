/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:24:07 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/03 16:49:56 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <libft/libft.h>
#include <interface/env.h>
#include "app.h"
#include "exec_data.h"
#include "builtins.h"
#include "envops.h"
#include "var_utils.h"

int	builtin_env(t_app *app, t_exec_data *ed)
{
	if (ed->args[1] != NULL)
	{
		ft_dprintf(2, "%s: env: %s: %s\n",
			app->name, ed->args[1], strerror(EINVAL));
		return (EINVAL);
	}
	vars_dprintf(ed->fd_out, "%s\n", app->env->vars);
	return (0);
}

int	builtin_export(t_app *app, t_exec_data *ed)
{
	int	i;
	int	err;

	if (ed->args[1] == NULL)
	{
		vars_dprintf(ed->fd_out, "export \"%s\"\n", app->env->vars);
		return (0);
	}
	err = 0;
	i = 1;
	while (ed->args[i] != NULL)
	{
		if (!var_is_assignment(ed->args[i]))
		{
			ft_dprintf(2, "%s: export: %s: %s\n",
				app->name, ed->args[i], strerror(EINVAL));
			err = EINVAL;
		}
		else
			env_vars_push(app->env, ed->args[i]);
		++i;
	}
	return (err);
}

int	builtin_unset(t_app *app, t_exec_data *ed)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (ed->args[i] != NULL)
	{
		if (!var_is_valid_name(ed->args[i]))
		{
			ft_dprintf(2, "%s: unset: %s: %s\n",
				app->name, ed->args[i], strerror(EINVAL));
			err = EINVAL;
		}
		else
			env_vars_remove(app->env, ed->args[i]);
		++i;
	}
	return (err);
}
