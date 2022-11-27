/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:43:27 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/27 15:09:21 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strjoin_char(char *s1, char s2)
{
	// TODO: this can be done much simpler without duplicating libft code
	// Remember that using libft is much better, even if a bit less performant,
	// because libft is well tested
	// this function can be implemented in just 3 lines:
	// - convert s2 char to string (2 lines)
	// - call ft_strjoin (1 line)
	char	*ret;
	size_t	s1_len;

	if (!s1 && !s2)
	{
		return (0);
	}
	else if (!s1)
	{
		return (ft_strdup(&s2)); //BUG: s2 is not NULL terminated!
	}
	s1_len = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (s1_len + 2));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, &s2, 2); //BUG: s2 is not NULL terminated!
	free(s1);
	return (ret);
}
