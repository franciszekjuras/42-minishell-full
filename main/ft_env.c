/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:37:24 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/19 17:13:23 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <env/env.h>

int	ft_env(t_envv *cur)
{
	while (cur->key != 0)
	{
		write(1, cur->key, ft_strlen(cur->key));
		write(1, "=", 1);
		write(1, cur->value, ft_strlen(cur->value));
		write(1, "\n", 1);
		cur = cur->next;
	}
	return (0);
}
