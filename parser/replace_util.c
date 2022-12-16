/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:11:34 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/16 11:47:45 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	if (s1 == NULL)
		return (ft_strdup(s2));
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
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
