/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:25:10 by chan-hpa          #+#    #+#             */
/*   Updated: 2022/12/01 23:56:14 by fjuras           ###   ########.fr       */
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

#define SHE 0
#define DFL 1
#define IGN 2

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

static void sigquit_handler(int signo)
{
	(void)signo;
}

void	main_init(int argc, char *argv[])
{
	struct termios	term;

	(void) argv;
	// TODO: exiting inside functions can be confusing. It would be much
	// better just to print the error here and propagate it with function return value
	// That way the caller can decide what to do with the error, e.g. in the main function
	// we might want to continue anyway, as extra arguments do no harm

	if (argc != 1)
		exit_with_err("argument input error", NULL, 126);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	if (isatty(0))
		signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	t_env			env;
	struct termios	term;
	t_line			parsed_line;

	tcgetattr(0, &term);
	main_init(argc, argv);
	minish_env_init(&env, envp);
	while (!env.should_exit)
	{
		g_shell_state = SHELL_STATE_PARSE;
		if (isatty(0))
			line = readline(get_prompt());
		else
			line = ft_get_next_line(0);
		g_shell_state = SHELL_STATE_EXEC;
		if (!line)
		{
			if (isatty(0))
				write(1, "\n", 1);
			break ;
		}
		if (*line != '\0')
			add_history(line);
		if (*line != '\0' && !is_whitespace(line))
		{
			parsed_line = parse(line, env);
			minish_execute(&env, parsed_line);
		}
		free(line);
	}
	minish_env_free(env);
	tcsetattr(0, TCSANOW, &term);
}
