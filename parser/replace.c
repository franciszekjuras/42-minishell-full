/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:44:28 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/27 15:41:19 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*replace_while_dollar(char str, char *new, t_envv *head, int quotes)
{
	static char	*env = NULL;

	if (ft_isalnum(str) || str == '_')
		env = ft_strjoin_char(env, str);
	else if (str == '?' && env == NULL)
	{
		env = ft_itoa(g_exit_code);
		new = ft_strjoin_free(new, env);
		env = ft_free(env);
	}
	else
	{
		if (env != NULL)
		{
			// TODO:
			// t_envv should be replaced with t_env and ft_getenv should be
			// modified to work with t_env
			new = ft_strjoin_free(new, ft_getenv(head, env));
			if (!(str == '\"' && quotes != 1) && !(str == '\'' && quotes != 2))
				new = ft_strjoin_char(new, str);
			env = ft_free(env);
			g_exit_code = 0;
		}
		else
			new = ft_strjoin_char(new, '$');
	}
	return (new);
}

static char	*replace_while_else(char c, char *new, int quotes)
{
	char	*result;

	result = NULL;
	if (c == -32)
		result = ft_strjoin_char(new, ' ');
	else if (!(c == '\"' && quotes != 1) && !(c == '\'' && quotes != 2))
	{
		result = ft_strjoin_char(new, c);
	}
	else
	{
		return (new);
	}
	return (result);
}

static int	dollar_check(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '$')
		return (1);
	else
		return (0);
}

static char	*replace_while(t_cmd *cmd, t_envv *head, int i)
{
	int		j;
	char	*new;
	int		dollar;
	int		quotes;

	quotes = 0;
	dollar = 0;
	j = 0;
	new = NULL;
	while (j <= (int)ft_strlen(cmd->argv[i]))
	{
		quotes = parse_set_quotes(cmd->argv[i][j], quotes, cmd);
		if (cmd->argv[i][j] == '$' && quotes != 1 && dollar == 0)
			dollar = 1;
		else if (dollar == 1)
		{
			new = replace_while_dollar(cmd->argv[i][j], new, head, quotes);
			dollar = dollar_check(cmd->argv[i][j]);
		}
		else
			new = replace_while_else(cmd->argv[i][j], new, quotes);
		j++;
	}
	return (new);
}

void	replace(t_cmd *cmd, t_envv *head)
{
	int		i;
	char	*new;

	while (cmd)
	{
		i = 0;
		while (i < cmd->argc)
		{
			new = replace_while(cmd, head, i);
			if (new == NULL && cmd->is_dollar)
				delete_argv(cmd, &i);
			else if (new == NULL)
			{
				new = ft_strdup("");
				argv_change(cmd, new, i);
			}
			else
				argv_change(cmd, new, i);
			i++;
			//printf("%s\n", new); // for testing
		}
		cmd = cmd->next;
	}
}
