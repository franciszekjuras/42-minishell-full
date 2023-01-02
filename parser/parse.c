/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:44:10 by chan-hpa          #+#    #+#             */
/*   Updated: 2023/01/02 21:34:18 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_cleanup(const char *err_str, char c, t_parse_data pd)
{
	if (err_str != NULL)
		ft_dprintf(2, "minish: parsing error: %s: %c\n", err_str, c);
	ft_free_list(pd.cmd);
	free(pd.str);
	return (0);
}

static t_line	make_default_line(void)
{
	t_line	empty_line;

	empty_line.progs = NULL;
	empty_line.size = 0;
	return (empty_line);
}

static int	parse_main_loop(char *line, t_parse_data *pd)
{
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (parse_cleanup(NULL, '\0', *pd));
	while (*line)
	{
		pd->quotes = parse_set_quotes(*line, pd->quotes, pd->cmd);
		if (*line == '|' && pd->quotes == 0)
		{
			if (!parse_in_pipe(pd))
				return (parse_cleanup("unexpected character", *line, *pd));
		}
		else if (!parse_out_pipe(line, pd))
			return (parse_cleanup("unexpected character", *line, *pd));
		line++;
	}
	return (1);
}

static int	parse_remainder(t_parse_data *pd)
{
	if (pd->quotes == 1)
		return (parse_cleanup("unclosed quote", '\'', *pd));
	if (pd->quotes == 2)
		return (parse_cleanup("unclosed quote", '\"', *pd));
	if (pd->str != NULL)
	{
		pd->cmd->argv = ft_split_argc(pd->str, &(pd->cmd->argc));
		if (pd->cmd->argc == 0)
			return (parse_cleanup("expected command after pipe", '|', *pd));
		pd->str = ft_free(pd->str);
	}
	else
		return (parse_cleanup("expected command after pipe", '|', *pd));
	return (1);
}

t_line	parse(char *line, t_env head)
{
	t_line			parsed_line;
	t_parse_data	pd;

	init_parse_data(&pd);
	if (!parse_main_loop(line, &pd))
		return (make_default_line());
	if (!parse_remainder(&pd))
		return (make_default_line());
	while (pd.cmd->prev != NULL)
		pd.cmd = pd.cmd->prev;
	replace(pd.cmd, head);
	parsed_line = translate(pd.cmd);
	(void) parse_cleanup(NULL, '\0', pd);
	return (parsed_line);
}
