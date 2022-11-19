/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:37:24 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/19 17:10:29 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./env.h"

int	ft_env(t_envv *cur)
{
	while (cur->key != 0)
	{
		ft_write(STDOUT_FILENO, cur->key, ft_strlen(cur->key));
		ft_write(STDOUT_FILENO, "=", 1);
		ft_write(STDOUT_FILENO, cur->value, ft_strlen(cur->value));
		ft_write(STDOUT_FILENO, "\n", 1);
		cur = cur->next;
	}
	return (EXIT_SUCCESS);
}
