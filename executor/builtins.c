/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:24:07 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/07 20:38:42 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include "builtins.h"

t_bltin_fun	builtin_resolve(const char *progname)
{
	if (progname == NULL)
		return (builtin_noop);
	else if (ft_strcmp(progname, "exit") == 0)
		return (builtin_exit);
	else if (ft_strcmp(progname, "echo") == 0)
		return (builtin_echo);
	else if (ft_strcmp(progname, "cd") == 0)
		return (builtin_cd);
	else if (ft_strcmp(progname, "pwd") == 0)
		return (builtin_pwd);
	else if (ft_strcmp(progname, "env") == 0)
		return (builtin_env);
	else if (ft_strcmp(progname, "export") == 0)
		return (builtin_export);
	else if (ft_strcmp(progname, "unset") == 0)
		return (builtin_unset);
	else
		return (NULL);
}

int	builtin_exit(t_app *app, t_exec_data *ed)
{
	char	*nstr;
	int		nval;
	int		err;

	app->env->should_exit = 1;
	if (ed->args[1] == NULL)
		return (app->env->last_exit_status);
	else if (ed->args[2] != NULL)
	{		
		ft_dprintf(2, "%s: exit: %s\n", app->name, "too many arguments");
		return (127);
	}
	else
	{
		nstr = ed->args[1];
		nval = ft_strtonum(&nstr, 0, 255, &err);
		if (*nstr != '\0' || err != 0)
		{
			ft_dprintf(2, "%s: exit: %s: %s\n", app->name, ed->args[1],
				"integer argument [0, 255] required");
			return (127);
		}
		return (nval);
	}
}

int	builtin_noop(t_app *app, t_exec_data *ed)
{
	(void)app;
	(void)ed;
	return (0);
}
