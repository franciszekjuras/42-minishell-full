/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:24:07 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/01 13:50:35 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include "builtins.h"

t_bltin_fun	builtin_resolve(const char *progname)
{
	if (ft_strcmp(progname, "exit") == 0)
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
	(void)ed;
	app->env->should_exit = 1;
	return (0);
}
