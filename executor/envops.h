/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envops.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:07:41 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/30 11:49:53 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVOPS_H
# define ENVOPS_H

void	env_free(t_env env);
void	env_update_path(t_env *env);
void	env_init(t_env *env, char **parent_environ);
void	env_vars_push(t_env *env, char *var);
void	env_vars_remove(t_env *env, char *var);

#endif
