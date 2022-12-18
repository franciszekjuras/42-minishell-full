/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:44:10 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/18 19:54:40 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_in_pipe(t_parse_data *pd)
{
	t_cmd	*next;

	if (pd->pipe == 1)
		return (0); // exit_with_err("argv error", "||", 1);
	pd->cmd->is_pipe = true;
	pd->cmd->argv = ft_split_argc(pd->str, &(pd->cmd->argc));
	next = ft_list_init();
	pd->cmd->next = next;
	next->prev = pd->cmd;
	pd->cmd = next;
	pd->str = ft_free(pd->str);
	pd->pipe = 1;
	return (1);
}

static char	*add_redirect_space(char *str, char *line, char c)
{
	if (c == '>')
	{
		line--;
		if (!(*line == '>' || *line == ' '))
			str = ft_strjoin_char(str, ' ');
		line++;
		str = ft_strjoin_char(str, -62);
		line++;
		if (!(*line == '>' || *line == ' '))
			str = ft_strjoin_char(str, ' ');
	}
	else if (c == '<')
	{
		line--;
		if (!(*line == '<' || *line == ' '))
			str = ft_strjoin_char(str, ' ');
		line++;
		str = ft_strjoin_char(str, -60);
		line++;
		if (!(*line == '<' || *line == ' '))
			str = ft_strjoin_char(str, ' ');
	}
	return (str);
}

static int	parse_out_pipe(char *line, t_parse_data *pd)
{
	if ((*line == ';' || *line == '\\') && pd->quotes == 0)
		return (0); // exit_with_err("symbol error", line, 1);
	else if (pd->quotes != 0 && *line == ' ')
		pd->str = ft_strjoin_char(pd->str, -32);
	else if (pd->quotes == 0 && ft_isspace(*line))
		pd->str = ft_strjoin_char(pd->str, ' ');
	else if ((*line == '>' || *line == '<') && pd->quotes == 0)
		pd->str = add_redirect_space(pd->str, line, *line);
	else
	{
		pd->str = ft_strjoin_char(pd->str, line[0]);
		pd->pipe = 0;
	}
	return (1);
}

t_line	parse(char *line, t_env head)
{
	t_line			parsed_line;
	t_parse_data	pd;

	init_parse_data(&pd);
	parsed_line.size = 0;
	while (*line)
	{
		pd.quotes = parse_set_quotes(*line, pd.quotes, pd.cmd);
		if (*line == '|' && pd.quotes == 0)
		{
			if (!parse_in_pipe(&pd))
				return (parsed_line);
		}
		else
		{
			if (!parse_out_pipe(line, &pd))
				return (parsed_line);
		}
		line++;
	}
	if (pd.quotes != 0)
		return (parsed_line); // exit_with_err("quotes error", NULL, 1);
	if (pd.str != NULL)
	{
		pd.cmd->argv = ft_split_argc(pd.str, &(pd.cmd->argc));
		pd.str = ft_free(pd.str);
	}
	while (pd.cmd->prev != NULL)
		pd.cmd = pd.cmd->prev;
	replace(pd.cmd, head);
	argc_checker(&pd.cmd);
	parsed_line = translate(pd.cmd);
	ft_free_list(pd.cmd);
	return (parsed_line);
}
