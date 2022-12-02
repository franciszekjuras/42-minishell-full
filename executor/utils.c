/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:22:54 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/02 20:11:46 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <libft/libft.h>

void	strarr_free(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i] != 0)
		free(strarr[i++]);
	free(strarr);
}

char	**extract_path_arr_from_env(char **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL && ft_strncmp(environ[i], "PATH=", 5) != 0)
		++i;
	if (environ[i] == NULL)
		return (ft_split("", ':'));
	else
		return (ft_split(environ[i] + 5, ':'));
}

int	check_if_path_is_executable(char *path, char *prog, char **candidate)
{
	char	*full_path;
	int		is_executable;

	is_executable = 0;
	full_path = ft_pathjoin(path, prog);
	if (access(full_path, F_OK) == 0)
	{
		free(*candidate);
		*candidate = ft_strdup(full_path);
		if (access(full_path, X_OK) == 0)
			is_executable = 1;
	}
	free(full_path);
	return (is_executable);
}

int	is_line_eq_str(char *line, char *str)
{
	char	*adv;

	adv = ft_str_advance_str(line, str);
	if (adv != NULL && (*adv == '\n' || *adv == '\0'))
		return (1);
	else
		return (0);
}
