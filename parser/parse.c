/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan-hpa <chan-hpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:44:10 by chan-hpa          #+#    #+#             */
/*   Updated: 2023/01/01 19:05:42 by chan-hpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_in_pipe(t_parse_data *pd)
{
	t_cmd	*next;

	if (pd->pipe == 1 || pd->str == NULL)
		return (0);
	pd->cmd->is_pipe = true;
	pd->cmd->argv = ft_split_argc(pd->str, &(pd->cmd->argc));
	if (pd->cmd->argc == 0)
		return (0);
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

static t_line	parse_err_cleanup(const char *err_str, char c, t_parse_data pd)
{
	t_line	empty_line;

	ft_dprintf(2, "minish: parsing error: %s: %c\n", err_str, c);
	ft_free_list(pd.cmd);
	free(pd.str);
	empty_line.progs = NULL;
	empty_line.size = 0;
	return (empty_line);
}

// t_line	check_parse_precondition(char *line, t_parse_data *pd, t_line parsed_line)
// {
// 	while (*line)
// 	{
// 		pd->quotes = parse_set_quotes(*line, pd->quotes, pd->cmd);
// 		if (*line == '|' && pd->quotes == 0)
// 		{
// 			if (!parse_in_pipe(pd))
// 				return (parse_err_cleanup("unexpected character", *line, *pd));
// 		}
// 		else if (!parse_out_pipe(line, pd))
// 			return (parse_err_cleanup("unexpected character", *line, *pd));
// 		line++;
// 	}
// 	if (pd->quotes == 1)
// 		return (parse_err_cleanup("unclosed quote", '\'', *pd));
// 	if (pd->quotes == 2)
// 		return (parse_err_cleanup("unclosed quote", '\"', *pd));
// 	return parsed_line;
// }

t_line	parse(char *line, t_env head)
{
	t_line			parsed_line;
	t_parse_data	pd;

	init_parse_data(&pd);
	parsed_line.size = 0;
	//check_parse_precondition(line, &pd, parsed_line);
	while (*line)
	{
		pd.quotes = parse_set_quotes(*line, pd.quotes, pd.cmd);
		if (*line == '|' && pd.quotes == 0)
		{
			if (!parse_in_pipe(&pd))
				return (parse_err_cleanup("unexpected character", *line, pd));
		}
		else if (!parse_out_pipe(line, &pd))
			return (parse_err_cleanup("unexpected character", *line, pd));
		line++;
	}
	if (pd.quotes == 1)
		return (parse_err_cleanup("unclosed quote", '\'', pd));
	if (pd.quotes == 2)
		return (parse_err_cleanup("unclosed quote", '\"', pd));
	if (pd.str != NULL)
	{
		pd.cmd->argv = ft_split_argc(pd.str, &(pd.cmd->argc));
		if (pd.cmd->argc == 0)
			return (parse_err_cleanup("expected command after pipe", '|', pd));
		pd.str = ft_free(pd.str);
	}
	else
		return (parse_err_cleanup("expected command after pipe", '|', pd));
	while (pd.cmd->prev != NULL)
		pd.cmd = pd.cmd->prev;
	replace(pd.cmd, head);
	argc_checker(&pd.cmd);
	parsed_line = translate(pd.cmd);
	ft_free_list(pd.cmd);
	return (parsed_line);
}
