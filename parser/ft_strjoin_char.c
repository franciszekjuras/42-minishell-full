/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:43:27 by chan-hpa          #+#    #+#             */
/*   Updated: 2023/01/02 20:41:47 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strjoin_char(char *s1, char s2)
{
	char	arr[2];

	arr[0] = s2;
	arr[1] = '\0';
	return (ft_strjoin_free(s1, arr));
}
