/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:47:42 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/01 14:42:13 by fjuras           ###   ########.fr       */
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

void	app_init(t_app *app, t_env *env, int line_size, const char *name);
void	app_free(t_app *app);
void	app_exec_line(t_app *app, t_line line);

#endif
