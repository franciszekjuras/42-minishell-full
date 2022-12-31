/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan-hpa <chan-hpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:46:48 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/31 23:33:15 by chan-hpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h> //for debugging
# include "struct.h"
# include <libft/libft.h>
# include <interface/line.h>
# include <interface/env.h>

typedef struct s_parse_data
{
	t_cmd	*cmd;
	char	*str;
	int		quotes;
	int		pipe;
}	t_parse_data;

typedef struct s_replace_data
{
	t_cmd	*cmd;
	t_env	env;
	int		dollar;
	int		quotes;
}	t_replace_data;

char	**ft_split_argc(char const *s, int *argc);
char	*ft_strjoin_char(char *s1, char s2);
int		parse_set_quotes(char line, int quotes, t_cmd *cmd);
t_line	parse(char *line, t_env env);
void	replace(t_cmd *cmd, t_env env);
void	replace_data_init(t_replace_data *rd, t_cmd *cmd, t_env env);
void	delete_argv(t_cmd *cmd, int *i);
void	argc_checker(t_cmd **cmd);
void	argv_change(t_cmd *cmd, char *new, int i);
char	*ft_strjoin_free(char *s1, char *s2);
void	init_parse_data(t_parse_data *pd);
t_line	translate(t_cmd *cmd);
int		dollar_check(char c);
void	ft_translate_redir_in_0(t_cmd *cur_cmd, t_line *line, int idx, int *i);
void	ft_translate_redir_in_1(t_cmd *cur_cmd, t_line *line, int idx, int *i);
void	ft_translate_redir_out_0(t_cmd *cur_cmd, t_line *line, int idx, int *i);
void	ft_translate_redir_out_1(t_cmd *cur_cmd, t_line *line, int idx, int *i);

#endif
