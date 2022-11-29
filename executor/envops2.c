/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envops2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:50:14 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/30 12:59:20 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/libft.h>
#include <interface/env.h>
#include "envops.h"
#include "var_utils.h"

static int	env_find_var(t_env *env, char *key)
{
	char	**var;
	char	*key_end;
	int		i;

	var = env->vars;
	i = 0;
	while (var[i])
	{
		key_end = ft_str_advance_str(var[i], key);
		if (key_end != NULL && *key_end == '=')
			return (i);
		i++;
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
	char	*key_end;
	char	**new_vars;

	key_end = var_find_name_end(var);
	*key_end = '\0';
	pos = env_find_var(env, var);
	*key_end = '=';
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
	int		i;

	pos = env_find_var(env, var);
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
