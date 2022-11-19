/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:04:13 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/06 18:54:15 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_DATA_H
# define EXEC_DATA_H

# include <sys/types.h>

struct						s_app;

typedef struct s_exec_data
{
	char	*prog_path;
	char	**args;
	int		fd_in;
	int		fd_out;
	int		fds[5];
	int		fds_end;
	int		pipe_next_fd;
	int		ready;
	int		is_builtin;
	int		(*builtin_fun)(struct s_app*, struct s_exec_data*);
}	t_exec_data;

void		exec_data_init(t_exec_data *exec_data);
void		exec_data_track_fd(t_exec_data *exec_data, int fd);
void		exec_data_close_tracked_fds(t_exec_data *exec_data);
void		exec_data_free(t_exec_data *exec_data);
t_exec_data	*exec_data_arr_init(int size);
void		exec_data_arr_free(t_exec_data *exec_data_arr, int size);

#endif