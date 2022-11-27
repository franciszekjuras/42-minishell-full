/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan-hpa <chan-hpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:08:36 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/27 17:12:37 by chan-hpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env/env.h>

char	*ft_getenv(t_envv *env_head, char *key)
{
	t_envv	*cur;

	cur = compare_env_key(env_head, key);
	return (cur->value);
}
