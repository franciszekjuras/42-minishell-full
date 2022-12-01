/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:10:26 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/01 16:49:14 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <signal.h>

# define SHELL_STATE_DEFAULT 1
# define SHELL_STATE_PARSE 1
# define SHELL_STATE_EXEC 2
# define SHELL_STATE_INTPT 3

extern volatile sig_atomic_t g_shell_state;

#endif
