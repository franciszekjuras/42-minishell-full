/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan-hpa <chan-hpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:11:34 by chan-hpa          #+#    #+#             */
/*   Updated: 2023/01/01 14:32:54 by chan-hpa         ###   ########.fr       */
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

void	replace_data_init(t_replace_data *rd, t_cmd *cmd, t_env env)
{
	rd->dollar = 0;
	rd->quotes = 0;
	rd->cmd = cmd;
	rd->env = env;
}
