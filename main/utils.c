/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:46:21 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/02 18:42:01 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libft/libft.h>
#include <interface/env.h>

#define MINISH_COLOR_NAME "\001\e[42m\002 mi\001\e[43m\002ni" \
	"\001\e[45m\002sh\001\e[44m\002ell \001\e[m\002"

void	exit_with_err(char *str1, char *str2, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	if (str2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str2, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}

void	*ft_malloc(size_t size, size_t n)
{
	void	*ret;

	ret = malloc(size * n);
	if (ret == NULL)
		exit_with_err("malloc()", strerror(errno), EXIT_FAILURE);
	return (ret);
}

int	is_whitespace(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
		{
			return (0);
		}
		line++;
	}
	return (1);
}

const char	*get_prompt(t_env env)
{
	if (env.last_exit_status == 0)
		return ("\001\e[1;36m\002*\001\e[m\002 " MINISH_COLOR_NAME " ");
	else if (env.last_exit_status > 128)
		return ("\001\e[1;31m\002*\001\e[m\002 " MINISH_COLOR_NAME " ");
	else
		return ("\001\e[1;33m\002*\001\e[m\002 " MINISH_COLOR_NAME " ");
}
