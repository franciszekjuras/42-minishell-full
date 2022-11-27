/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:09:22 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/11/27 19:36:19 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

# include <stdbool.h>
# include <stdlib.h>

typedef struct s_cmd
{
	char			**argv;
	int				argc;
	bool			is_pipe;
	bool			is_dollar;
	int				fd[2];
	int				infile;
	int				outfile;
	char			*cmd_path;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}						t_cmd;

void		*ft_free(void *ptr);
t_cmd		*ft_list_init(void);
void		ft_free_list(t_cmd *cmd);

#endif
