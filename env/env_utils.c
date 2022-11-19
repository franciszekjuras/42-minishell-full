/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:16:23 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/19 17:10:24 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./env.h"

char	*get_env_key(char *key_value)
{
	size_t	i;
	size_t	len;
	char	*key;

	len = 0;
	while (key_value[len] != 0 && key_value[len] != '=')
		++len;
	if (key_value[len] == '\0')
		return (NULL);
	key = (char *)ft_malloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		key[i] = key_value[i];
		++i;
	}
	key[i] = 0;
	return (key);
}

char	*get_env_value(char *key_value)
{
	size_t	i;
	size_t	len;
	char	*value;

	len = 0;
	while (key_value[len] != 0 && key_value[len] != '=')
		++key_value;
	if (key_value[len] == 0)
		return (NULL);
	len = ft_strlen(++key_value);
	value = (char *)ft_malloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		value[i] = key_value[i];
		++i;
	}
	value[i] = 0;
	return (value);
}

t_envv	*compare_env_key(t_envv *env_head, char *key)
{
	t_envv	*cur;

	cur = env_head;
	while (cur->key != 0 && ft_strncmp(key, cur->key, ft_strlen(cur->key)))
		cur = cur->next;
	return (cur);
}

t_envv	*new_env(char *key_value)
{
	t_envv	*new;

	new = (t_envv *)ft_malloc(sizeof(t_envv), 1);
	if (key_value == NULL)
	{
		new->key = NULL;
		new->value = NULL;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		new->key = get_env_key(key_value);
		if (new->key == NULL)
			return (NULL);
		new->value = get_env_value(key_value);
		if (new->value == NULL)
			return (NULL);
		new->next = NULL;
		new->prev = NULL;
	}
	printf("%s %s\n", new->key, new->value); // for testing
	return (new);
}

int	init_env_list(t_envv *cur, char **envp)
{
	size_t	i;
	t_envv	*new;

	i = 0;
	cur->key = get_env_key(envp[i]);
	if (cur->key == NULL)
		return (-1);
	cur->value = get_env_value(envp[i]);
	if (cur->value == NULL)
		return (-1);
	cur->next = 0;
	cur->prev = 0;
	while (envp[++i])
	{
		new = new_env(envp[i]);
		if (new == NULL)
			return (-1);
		cur->next = new;
		new->prev = cur;
		cur = cur->next;
	}
	new = new_env(NULL);
	new->prev = cur;
	cur->next = new;
	return (0);
}
