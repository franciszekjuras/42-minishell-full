/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_priv.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:21:08 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/02 17:19:00 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_PRIV_H
# define APP_PRIV_H

# include <interface/line.h>
# include "app.h"
# include "exec_data.h"

char	*app_resolve_prog_path(t_app *app, char *prog);
void	app_exec_child_side(t_app *app, t_exec_data *exec_data);
void	app_exec_builtin(t_app *app, t_exec_data *exec_data);
int		app_pipe(t_app *app,
			t_exec_data *exec_data_in, t_exec_data *exec_data_out);
int		app_open(t_app *app, t_exec_data *exec_data, char *file, int mode);
void	app_fill_exec_data(t_app *app, t_exec_data *exec_data, t_prog prog);
int		app_pipe_exec_data_arr(t_app *app,
			t_exec_data *exec_data_arr, int i, int size);
void	app_exec(t_app *app, t_exec_data *exec_data);

#endif
