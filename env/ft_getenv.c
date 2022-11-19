/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:08:36 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/19 17:10:39 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./env.h"

char	*ft_getenv(t_envv *env_head, char *key)
{
	t_envv	*cur;

	cur = compare_env_key(env_head, key);
	return (cur->value);
}
