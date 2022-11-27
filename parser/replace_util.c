/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:11:34 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/27 18:04:00 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// TODO: This function name is misleading: which string is free'd?
// Better name would be str_append - that way it's clear that first string is modified
char	*ft_strjoin_free(char *s1, char *s2)
{
// TODO: Don't reimplement libft functions when customizing them
// Using ft_strjoin you can implement it in 3 lines:
// - call ft_strjoin
// - free s1
// - return joined string
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *)ft_malloc(sizeof(char), (s1_len + s2_len + 1));
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, s2, s2_len + 1);
	free(s1);
	return (ret);
}

void	delete_argv(t_cmd *cmd, int *i)
{
	int		tmp;

	tmp = *i;
	cmd->argv[tmp] = ft_free(cmd->argv[tmp]);
	while (tmp < cmd->argc - 1)
	{
		cmd->argv[tmp] = cmd->argv[tmp + 1];
		tmp++;
	}
	*i = *i - 1;
	cmd->argc = cmd->argc - 1;
	cmd->is_dollar = false;
	cmd->argv[tmp] = 0;
}

void	argv_change(t_cmd *cmd, char *new, int i)
{
	cmd->argv[i] = ft_free(cmd->argv[i]);
	cmd->argv[i] = new;
}
