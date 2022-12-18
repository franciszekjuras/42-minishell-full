/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan-hpa <chan-hpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:43:27 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/27 16:58:47 by chan-hpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strjoin_char(char *s1, char s2)
{
	char	arr[2];

	arr[0] = s2;
	arr[1] = '\0';
	if (s1 == NULL)
	{
		return (ft_strdup(arr));
	}
	return (ft_strjoin(s1, arr));
}
