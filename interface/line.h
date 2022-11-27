/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan-hpa <chan-hpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:50:14 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/20 17:50:54 by chan-hpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

typedef struct s_redir
{
	char	*path;
}	t_redir;

typedef struct s_prog
{
	t_redir	in_redir;
	t_redir	out_redir;
	char	**args;
}	t_prog;

typedef struct s_line
{
	t_prog	*progs;
	int		size;
}	t_line;

#endif
