/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan-hpa <chan-hpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:26:08 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/31 23:31:51 by chan-hpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_translate_redir_in_0(t_cmd *cur_cmd, t_line *line, int idx, int *i)
{
	line->progs[idx].in_redir.path = ft_strdup(cur_cmd->argv[++*(i)]);
	line->progs[idx].in_redir.is_alt = 0;
}

void	ft_translate_redir_in_1(t_cmd *cur_cmd, t_line *line, int idx, int *i)
{
	line->progs[idx].in_redir.path = ft_strdup(cur_cmd->argv[++*(i)]);
	line->progs[idx].in_redir.is_alt = 1;
}

void	ft_translate_redir_out_0(t_cmd *cur_cmd, t_line *line, int idx, int *i)
{
	line->progs[idx].out_redir.path = ft_strdup(cur_cmd->argv[++*(i)]);
	line->progs[idx].out_redir.is_alt = 0;
}

void	ft_translate_redir_out_1(t_cmd *cur_cmd, t_line *line, int idx, int *i)
{
	line->progs[idx].out_redir.path = ft_strdup(cur_cmd->argv[++*(i)]);
	line->progs[idx].out_redir.is_alt = 1;
}
