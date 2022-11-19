/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:50:14 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/19 17:44:57 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <libft/libft.h>
#include "var_utils.h"

char	*var_find_name_end(char *var)
{
	return (ft_strchr(var, '='));
}

/*
https://stackoverflow.com/questions/2821043/allowed-characters-in-linux-environment-variable-names
Environment variable names used by the utilities in the Shell 
and Utilities volume of IEEE Std 1003.1-2001 consist solely 
of uppercase letters, digits, and the '_' (underscore) from
the characters defined in Portable Character Set and do not 
begin with a digit.
*/

int	var_is_valid_name(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[i]))
		return (0);
	while (var[i] != '\0')
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (0);
		++i;
	}
	return (1);
}

int	var_is_assignment(char *var)
{
	char	*var_name_end;
	int		is_valid_name;

	var_name_end = var_find_name_end(var);
	if (var_name_end == NULL)
		return (0);
	*var_name_end = '\0';
	is_valid_name = var_is_valid_name(var);
	*var_name_end = '=';
	return (is_valid_name);
}

void	vars_dprintf(int fd, const char *format, char **vars)
{
	int	i;

	i = 0;
	while (vars[i] != NULL)
		ft_dprintf(fd, format, vars[i++]);
}
