/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:44:28 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/15 22:48:40 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_env(t_env env, char *key)
{
	char	**var;
	char	*key_end;

	var = env.vars;
	while (*var)
	{
		key_end = ft_str_advance_str(*var, key);
		if (key_end != NULL && *key_end == '=')
			return (key_end + 1);
		var++;
	}
	return ("");
}

static char	*replace_while_dollar(char str, char *new, t_env env, int quotes)
{
	static char	*env_var = NULL;

	if (ft_isalnum(str) || str == '_')
		env_var = ft_strjoin_char(env_var, str);
	else if (str == '?' && env_var == NULL)
	{
		env_var = ft_itoa(env.last_exit_status);
		new = ft_strjoin_free(new, env_var);
		env_var = ft_free(env_var);
	}
	else
	{
		if (env_var != NULL)
		{
			new = ft_strjoin_free(new, get_env(env, env_var));
			if (!(str == '\"' && quotes != 1) && !(str == '\'' && quotes != 2))
				new = ft_strjoin_char(new, str);
			env_var = ft_free(env_var);
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
	else if (c == -60)
		result = ft_strjoin_char(new, '<');
	else if (c == -62)
		result = ft_strjoin_char(new, '>');
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

static char	*replace_while(t_cmd *cmd, t_env env, int i)
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
			new = replace_while_dollar(cmd->argv[i][j], new, env, quotes);
			dollar = dollar_check(cmd->argv[i][j]);
		}
		else
			new = replace_while_else(cmd->argv[i][j], new, quotes);
		j++;
	}
	return (new);
}

void	replace(t_cmd *cmd, t_env env)
{
	int		i;
	char	*new;

	while (cmd)
	{
		i = 0;
		while (i < cmd->argc)
		{
			new = replace_while(cmd, env, i);
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
		}
		cmd = cmd->next;
	}
}
