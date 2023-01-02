/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:44:10 by chan-hpa          #+#    #+#             */
/*   Updated: 2023/01/02 21:56:06 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_in_pipe(t_parse_data *pd)
{
	t_cmd	*next;

	if (pd->pipe == 1 || pd->str == NULL)
		return (0);
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

char	*add_redirect_space(char *str, char *line, char c)
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

int	parse_out_pipe(char *line, t_parse_data *pd)
{
	if ((*line == ';' || *line == '\\') && pd->quotes == 0)
		return (0);
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
