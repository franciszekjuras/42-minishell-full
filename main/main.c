/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:25:10 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/02 12:56:01 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <stdio.h> //for testing
#include <readline/history.h>
#include <libft/libft.h>
#include <parser/parser.h>
#include <interface/env.h>
#include <interface/line.h>
#include <interface/global.h>
#include <executor/executor.h>

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/errno.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "utils.h"

volatile sig_atomic_t	g_shell_state = 0;

static void	sigint_handler(int signo)
{
	(void)signo;
	if (g_shell_state == SHELL_STATE_PARSE)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_shell_state == SHELL_STATE_EXEC)
		g_shell_state = SHELL_STATE_INTPT;
}

static void	sigquit_handler(int signo)
{
	(void)signo;
}

static void	main_init(int argc, char *argv[])
{
	struct termios	term;
	int				i;

	i = 1;
	while (i < argc)
		ft_dprintf(2, "%s: warning: ignored argument: %s\n",
			argv[0], argv[i++]);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	if (isatty(0))
		signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

static	void read_and_exec_line(t_env *env)
{
	char			*line;
	t_line			parsed_line;

	g_shell_state = SHELL_STATE_PARSE;
	if (isatty(0))
		line = readline(get_prompt(*env));
	else
		line = ft_get_next_line(0);
	g_shell_state = SHELL_STATE_EXEC;
	if (!line)
	{
		if (isatty(0))
			write(1, "\n", 1);
		env->should_exit = 1;
		return ;
	}
	if (*line != '\0')
		add_history(line);
	if (*line != '\0' && !is_whitespace(line))
	{
		parsed_line = parse(line, *env);
		minish_execute(env, parsed_line);
	}
	free(line);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env			env;
	struct termios	term;

	tcgetattr(0, &term);
	main_init(argc, argv);
	minish_env_init(&env, envp);
	while (!env.should_exit)
	{
		read_and_exec_line(&env);
	}
	minish_env_free(env);
	tcsetattr(0, TCSANOW, &term);
}
