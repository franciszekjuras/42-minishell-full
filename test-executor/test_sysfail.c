/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sysfail.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:28:02 by fjuras            #+#    #+#             */
/*   Updated: 2022/12/01 19:12:06 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Test name abbreviations:
#C -- # commands
iR -- input redirection
oR -- output redirection
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <executor/executor.h>
#include <interface/env.h>
#include <interface/line.h>
#include <interface/global.h>
#include <interface/test_framework.h>

#define GREP "/usr/bin/grep"
#define CAT "/usr/bin/cat"
#define SLEEP "/usr/bin/sleep"
#define MEG "./megaphone"
#define SEGF "./segfaulter.sh"

#define SIGCODE(x) (128 + (x))

volatile sig_atomic_t g_shell_state = 0;

typedef struct s_test_data
{
	int		i;
	int		retval;
	int		retval_match;
	int		file_match;
}	t_test_data;

t_env	g_env;

static void	sigint_handler(int signo)
{
	(void)signo;
	g_shell_state = SHELL_STATE_INTPT;
}

int	test_2C_2nd_fork_fail(const char *filter)
{
	t_line		line;
	t_test_data	d;

	TEST_START_CLEAN(filter);
	d.i = 0;
	test_line_init(&line, 2);
	test_prog_args(&line.progs[d.i], MEG, "i", "am", "the", "walrus", NULL);
	test_prog_redirs(&line.progs[d.i++], NULL, NULL);
	test_prog_args(&line.progs[d.i], GREP, "THE", NULL);
	test_prog_redirs(&line.progs[d.i++], NULL, NULL);
	test_line_end(&line, d.i);
	test_redirect_stdout("out/stdout.txt");
	d.retval = minish_execute(&g_env, line);
	test_close_stdout();
	d.file_match = test_expect_file_content("out/stdout.txt", NULL);
	d.retval_match = test_expect_retval(d.retval, EAGAIN);
	return (TEST_END(d.retval_match && d.file_match));
}

int	test_2C_pipe_fail(const char *filter)
{
	t_line		line;
	t_test_data	d;

	TEST_START_CLEAN(filter);
	d.i = 0;
	test_line_init(&line, 2);
	test_prog_args(&line.progs[d.i], MEG, "i", "am", "the", "walrus", NULL);
	test_prog_redirs(&line.progs[d.i++], NULL, NULL);
	test_prog_args(&line.progs[d.i], GREP, "THE", NULL);
	test_prog_redirs(&line.progs[d.i++], NULL, NULL);
	test_line_end(&line, d.i);
	test_redirect_stdout("out/stdout.txt");
	d.retval = minish_execute(&g_env, line);
	test_close_stdout();
	d.file_match = test_expect_file_content("out/stdout.txt", NULL);
	d.retval_match = test_expect_retval(d.retval, ENFILE);
	return (TEST_END(d.retval_match && d.file_match));
}

int	test_builtin_pwd_fail(const char *filter)
{
	t_line		line;
	t_test_data	d;

	TEST_START_CLEAN(filter);
	d.i = 0;
	test_line_init(&line, 1);
	test_prog_args(&line.progs[d.i], "pwd", NULL);
	test_prog_redirs(&line.progs[d.i++], NULL, NULL);
	test_line_end(&line, d.i);
	test_redirect_stdout("out/stdout.txt");
	d.retval = minish_execute(&g_env, line);
	test_close_stdout();
	d.file_match = test_expect_file_content("out/stdout.txt", NULL);
	d.retval_match = test_expect_retval(d.retval, ENOENT);
	return (TEST_END(d.retval_match && d.file_match));
}

int	test_heredoc_pipe_fail(const char *filter)
{
	t_line		line;
	t_test_data	d;

	TEST_START_CLEAN(filter);
	d.i = 0;
	test_line_init(&line, 1);
	test_prog_args(&line.progs[d.i], CAT, NULL);
	test_prog_redirs(&line.progs[d.i], "mouse", NULL);
	line.progs[d.i++].in_redir.is_alt = 1;
	test_line_end(&line, d.i);
	test_redirect_stdout("out/stdout.txt");
	test_redirect_stdin("in/animals.txt");
	d.retval = minish_execute(&g_env, line);
	test_restore_stdin();
	test_close_stdout();
	d.file_match = test_expect_file_content("out/stdout.txt", NULL);
	d.retval_match = test_expect_retval(d.retval, ENFILE);
	return (TEST_END(d.retval_match && d.file_match));
}

int test_sigint(const char *filter)
{
	t_line		line;
	t_test_data	d;

	TEST_START_CLEAN(filter);
	fprintf(stderr, "Press Ctrl-C...\n");
	d.i = 0;
	test_line_init(&line, 6);
	test_prog_args(&line.progs[d.i], SLEEP, "10", NULL);
	test_prog_redirs(&line.progs[d.i++], NULL, NULL);
	test_prog_args(&line.progs[d.i], MEG, "hello", NULL);
	test_prog_redirs(&line.progs[d.i++], NULL, NULL);
	test_prog_args(&line.progs[d.i], SLEEP, "10", NULL);
	test_prog_redirs(&line.progs[d.i++], NULL, NULL);
	test_prog_args(&line.progs[d.i], MEG, "i", "am", "the", "walrus", NULL);
	test_prog_redirs(&line.progs[d.i++], NULL, NULL);
	test_prog_args(&line.progs[d.i], GREP, "THE", NULL);
	test_prog_redirs(&line.progs[d.i++], NULL, NULL);
	test_prog_args(&line.progs[d.i], SLEEP, "10", NULL);
	test_prog_redirs(&line.progs[d.i++], NULL, NULL);
	test_line_end(&line, d.i);
	test_redirect_stdout("out/stdout.txt");
	d.retval = minish_execute(&g_env, line);
	test_close_stdout();
	d.file_match = 1;
	d.retval_match = test_expect_retval(d.retval, SIGCODE(SIGINT));
	return (TEST_END(d.retval_match && d.file_match));
}

const t_test_function g_test_functions[] =
{
	test_2C_2nd_fork_fail,
	test_2C_pipe_fail,
	test_builtin_pwd_fail,
	test_heredoc_pipe_fail,
	test_sigint,
	NULL
};

int main (int argc, char **argv)
{
	int	retval;

	signal(SIGINT, sigint_handler);
	minish_env_init(&g_env, NULL);
	retval = test_main(argc, argv);
	minish_env_free(g_env);
	return (retval);
}
