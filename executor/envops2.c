/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envops2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:50:14 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/07 13:46:18 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/libft.h>
#include <interface/env.h>
#include "envops.h"
#include "var_utils.h"

int	env_vars_find_l(t_env *env, char *var, int var_name_len)
{
	int		i;

	i = 0;
	while (env->vars[i] != NULL)
	{
		if (ft_strncmp(env->vars[i], var, var_name_len + 1) == 0)
			return (i);
		++i;
	}
	return (i);
}

static void	vars_move(char **src, char **dest)
{
	int	i;

	i = 0;
	while (src[i] != NULL)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = NULL;
	free(src);
}

void	env_vars_push(t_env *env, char *var)
{
	int		pos;
	char	**new_vars;

	pos = env_vars_find_l(env, var, var_find_name_end(var) - var);
	if (env->vars[pos] != NULL)
	{
		free(env->vars[pos]);
		env->vars[pos] = ft_strdup(var);
	}
	else
	{
		new_vars = ft_calloc(pos + 2, sizeof(char *));
		vars_move(env->vars, new_vars);
		new_vars[pos] = ft_strdup(var);
		new_vars[pos + 1] = NULL;
		env->vars = new_vars;
	}
	if (ft_strncmp(var, "PATH=", 5) == 0)
		env_update_path(env);
}

void	env_vars_remove(t_env *env, char *var)
{
	int		pos;
	int		var_len;
	int		i;

	var_len = ft_strlen(var);
	var[var_len] = '=';
	pos = env_vars_find_l(env, var, var_len);
	var[var_len] = '\0';
	if (pos < 0 || env->vars[pos] == NULL)
		return ;
	free(env->vars[pos]);
	i = pos;
	while (env->vars[i] != NULL)
	{
		env->vars[i] = env->vars[i + 1];
		++i;
	}
	if (ft_strcmp(var, "PATH") == 0)
		env_update_path(env);
}
