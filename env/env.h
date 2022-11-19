/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:41:40 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/19 17:10:10 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <libft/libft.h>

typedef struct s_envv
{
	char			*key;
	char			*value;
	struct s_envv	*next;
	struct s_envv	*prev;
}	t_envv;

extern int g_exit_code;

t_envv	*dup_env_list(t_envv *cur);
t_envv	*sort_env_list(t_envv *head);
void	free_env_list(t_envv *env);

int		check_valid_identifier(int argc, char *argv[]);
int		is_all_digit(char *key_value, char set);
int		is_have_space(char *key_value, char set);
int		is_have_specific_char(char *key_value, char c);

int		init_env_list(t_envv *cur, char **envp);
t_envv	*new_env(char *key_value);
char	*get_env_key(char *key_value);
char	*get_env_value(char *key_value);
t_envv	*compare_env_key(t_envv *env_head, char *key);
char	*ft_getenv(t_envv *env_head, char *key);

#endif
