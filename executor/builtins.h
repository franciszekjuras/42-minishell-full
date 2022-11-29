/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:23:35 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/30 12:40:03 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <interface/env.h>
# include "app.h"
# include "exec_data.h"

typedef int	(*t_bltin_fun)(t_app *, t_exec_data *);

t_bltin_fun	builtin_resolve(const char *progname);
int			builtin_echo(t_app *app, t_exec_data *ed);
int			builtin_cd(t_app *app, t_exec_data *ed);
int			builtin_pwd(t_app *app, t_exec_data *ed);
int			builtin_env(t_app *app, t_exec_data *ed);
int			builtin_export(t_app *app, t_exec_data *ed);
int			builtin_unset(t_app *app, t_exec_data *ed);

#endif