/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:44:28 by chan-hpa          #+#    #+#             */
/*   Updated: 2023/01/02 21:51:07 by fjuras           ###   ########.fr       */
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

static char	*replace_while_dollar(
	char c, char *new, char **env_var, t_replace_data rd)
{
	if (ft_isalnum(c) || c == '_')
		*env_var = ft_strjoin_char(*env_var, c);
	else if (c == '?' && *env_var == NULL)
	{
		*env_var = ft_itoa(rd.env.last_exit_status);
		new = ft_strjoin_free(new, *env_var);
		*env_var = ft_free(*env_var);
	}
	else
	{
		if (*env_var != NULL)
		{
			new = ft_strjoin_free(new, get_env(rd.env, *env_var));
			if (!(c == '\"' && rd.quotes != 1)
				&& !(c == '\'' && rd.quotes != 2))
				new = ft_strjoin_char(new, c);
			*env_var = ft_free(*env_var);
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

static char	*replace_while(t_cmd *cmd, t_env env, int i)
{
	int				j;
	char			*new;
	char			*env_var;
	t_replace_data	rd;

	replace_data_init(&rd, cmd, env);
	j = 0;
	new = ft_strdup("");
	env_var = NULL;
	while (j <= (int)ft_strlen(cmd->argv[i]))
	{
		rd.quotes = parse_set_quotes(cmd->argv[i][j], rd.quotes, cmd);
		if (cmd->argv[i][j] == '$' && rd.quotes != 1 && rd.dollar == 0)
			rd.dollar = 1;
		else if (rd.dollar == 1)
		{
			new = replace_while_dollar(cmd->argv[i][j], new, &env_var, rd);
			rd.dollar = dollar_check(cmd->argv[i][j]);
		}
		else
			new = replace_while_else(cmd->argv[i][j], new, rd.quotes);
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
			argv_change(cmd, new, i);
			i++;
		}
		cmd = cmd->next;
	}
}
