/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_arg_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:12:35 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/19 17:13:27 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <env/env.h>
#include "utils.h"

static void	swap_env(t_envv *env1, t_envv *env2)
{
	char	*tmp_k;
	char	*tmp_v;

	tmp_k = env1->key;
	tmp_v = env1->value;
	env1->key = env2->key;
	env1->value = env2->value;
	env2->key = tmp_k;
	env2->value = tmp_v;
}

static t_envv	*dup_env(t_envv *cur)
{
	t_envv	*new;

	new = (t_envv *)ft_malloc(sizeof(t_envv), 1);
	if (cur == NULL)
	{
		new->key = NULL;
		new->value = NULL;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		new->key = ft_strdup(cur->key);
		new->value = ft_strdup(cur->value);
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

t_envv	*dup_env_list(t_envv *cur)
{
	t_envv	*ret;
	t_envv	*new;
	t_envv	*tmp;

	ret = dup_env(cur);
	tmp = ret;
	cur = cur->next;
	while (cur->key)
	{
		new = dup_env(cur);
		tmp->next = new;
		new->prev = tmp;
		tmp = new;
		cur = cur->next;
	}
	new = dup_env(NULL);
	tmp->next = new;
	new->prev = tmp;
	return (ret);
}

t_envv	*sort_env_list(t_envv *head)
{
	t_envv	*cur;

	cur = head;
	while (cur->next->key)
	{
		if (ft_strcmp(cur->key, cur->next->key) > 0)
		{
			swap_env(cur, cur->next);
			cur = head;
		}
		else
			cur = cur->next;
	}
	return (head);
}

void	free_env_list(t_envv *env)
{
	t_envv	*next;

	while (env->key)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
	free(env->key);
	free(env->value);
	free(env);
}
