/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:46:21 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/16 11:49:52 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libft/libft.h>

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
