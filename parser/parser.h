/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:46:48 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/16 12:51:10 by fjuras           ###   ########.fr       */
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

char	**ft_split_argc(char const *s, char c, int *argc);
char	*ft_strjoin_char(char *s1, char s2);
int		parse_set_quotes(char line, int quotes, t_cmd *cmd);
t_line	parse(char *line,  t_env env);
void	replace(t_cmd *cmd, t_env env);
void	delete_argv(t_cmd *cmd, int *i);
void	argc_checker(t_cmd **cmd);
void	argv_change(t_cmd *cmd, char *new, int i);
char	*ft_strjoin_free(char *s1, char *s2);
void	init_parse_data(t_parse_data *pd);
t_line	translate(t_cmd *cmd);

#endif
