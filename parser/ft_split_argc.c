/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_argc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:41:04 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/18 19:55:48 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**ft_split_argc(char const *s, int *argc)
{
	char	**argv;
	int		i;

	argv = ft_split(s, ' ');
	i = 0;
	while (argv[i] != NULL)
		++i;
	*argc = i;
	return (argv);
}
