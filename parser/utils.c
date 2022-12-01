/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:46:21 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/01 20:31:22 by fjuras           ###   ########.fr       */
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

// TODO: delete after fixing ft_strjoin_free
void	*ft_malloc(size_t size, size_t n)
{
	void	*ret;

	ret = malloc(size * n);
	if (ret == NULL)
		exit_with_err("malloc()", strerror(errno), EXIT_FAILURE);
	return (ret);
}
