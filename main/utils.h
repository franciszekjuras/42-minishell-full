/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:37:36 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/02 12:43:53 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void		exit_with_err(char *str1, char *str2, int exit_code);
void		*ft_malloc(size_t size, size_t n);
int			is_whitespace(char *line);
const char	*get_prompt(t_env env);

#endif
