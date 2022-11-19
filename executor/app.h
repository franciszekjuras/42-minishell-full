/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:47:42 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/04 14:42:04 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include <sys/types.h>
# include <interface/env.h>
# include <interface/line.h>
# include "exec_data.h"
# include "childs.h"

# define APP_OPEN_IN 1
# define APP_OPEN_OUT 2

typedef struct s_app
{
	char		*name;
	t_env		*env;
	t_childs	childs;
	int			builtin_last_retval;
}	t_app;

void	app_init(t_app *app, t_env *env, const char *name);
void	app_free(t_app *app);
void	app_exec_arr(t_app *app, t_exec_data *exec_data_arr, t_line line);

#endif
