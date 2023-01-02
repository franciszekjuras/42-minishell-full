/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:11:34 by chan-hpa          #+#    #+#             */
/*   Updated: 2023/01/02 21:51:49 by fjuras           ###   ########.fr       */
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
