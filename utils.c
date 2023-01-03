/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:46:21 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/16 12:50:43 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libft/libft.h>
#include <interface/env.h>

#define MINISH_COLOR_NAME1 "\001\e[42m\002 mi\001\e[43m\002ni"
#define MINISH_COLOR_NAME2 "\001\e[45m\002sh\001\e[44m\002ell \001\e[m\002"

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
		return ("\001\e[1;36m\002*\001\e[m\002 "
			MINISH_COLOR_NAME1 MINISH_COLOR_NAME2 " ");
	else if (env.last_exit_status > 128)
		return ("\001\e[1;31m\002*\001\e[m\002 "
			MINISH_COLOR_NAME1 MINISH_COLOR_NAME2 " ");
	else
		return ("\001\e[1;33m\002*\001\e[m\002 "
			MINISH_COLOR_NAME1 MINISH_COLOR_NAME2 " ");
}
