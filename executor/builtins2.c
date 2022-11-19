/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:24:07 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/08 19:15:07 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libft/libft.h>
#include "exec_data.h"
#include "app.h"
#include "builtins.h"

int	builtin_echo(t_app *app, t_exec_data *ed)
{
	int	i;
	int	print_newline;

	(void)app;
	i = 1;
	print_newline = 0;
	if (ed->args[i] != NULL && ft_strcmp(ed->args[i], "-n") == 0)
		++i;
	else
		print_newline = 1;
	while (ed->args[i] != NULL)
	{
		ft_putstr_fd(ed->args[i], ed->fd_out);
		if (ed->args[i + 1] != NULL)
			ft_putchar_fd(' ', ed->fd_out);
		++i;
	}
	if (print_newline)
		ft_putchar_fd('\n', ed->fd_out);
	return (0);
}

int	builtin_cd(t_app *app, t_exec_data *ed)
{
	char	*err_str;

	if (ed->args[1] == NULL || ed->args[2] != NULL)
	{
		if (ed->args[1] == NULL)
			err_str = "one argument required";
		else
			err_str = "too many arguments";
		ft_dprintf(2, "%s: %s: %s\n", app->name, ed->args[0], err_str);
		return (EPERM);
	}
	if (chdir(ed->args[1]) != 0)
	{
		ft_dprintf(2, "%s: %s: %s: %s\n",
			app->name, ed->args[0], ed->args[1], strerror(errno));
		return (errno);
	}
	return (0);
}

int	builtin_pwd(t_app *app, t_exec_data *ed)
{
	char	*wd_str;

	wd_str = getcwd(NULL, 0);
	if (wd_str == NULL)
	{
		ft_dprintf(2, "%s: %s: %s\n", app->name, ed->args[0], strerror(errno));
		return (errno);
	}
	ft_dprintf(ed->fd_out, "%s\n", wd_str);
	free(wd_str);
	return (0);
}
