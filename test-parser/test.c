/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:12:03 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/27 21:48:44 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <interface/env.h>
#include <interface/line.h>
#include <interface/test_framework.h>
#include <parser/parser.h>

t_env	g_env;

int	test_single_cmd(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], "ls", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = parse("ls", g_env);
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line); test_line_free(expect);
	return (TEST_END(res));
}

int	test_cmd_with_arg(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], "grep", "total", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = parse("grep total", g_env);
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line); test_line_free(expect);
	return (TEST_END(res));
}

int	test_two_cmds(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 2);
	test_prog_args(&expect.progs[i], "ls", "-l", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_prog_args(&expect.progs[i], "grep", "total", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = parse("ls -l | grep total", g_env);
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line); test_line_free(expect);
	return (TEST_END(res));
}

int	test_redir(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], "ls", NULL);
	test_prog_redirs(&expect.progs[i++], "in.txt", "out.txt");
	test_line_end(&expect, i);
	line = parse("<in.txt ls >out.txt", g_env);
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line); test_line_free(expect);
	return (TEST_END(res));
}

int	test_env(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], "a", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = parse("$A", g_env);
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line); test_line_free(expect);
	return (TEST_END(res));
}

int	test_double_quote(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], "one string", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = parse("\"one string\"", g_env);
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line); test_line_free(expect);
	return (TEST_END(res));
}


int	test_single_quote(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], "one string", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = parse("\'one string\'", g_env);
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line); test_line_free(expect);
	return (TEST_END(res));
}

int	test_dq_env(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], "a", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = parse("\"$A\"", g_env);
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line); test_line_free(expect);
	return (TEST_END(res));
}

int	test_env_w_space(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], "ls", "-l", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = parse("$LS", g_env);
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line); test_line_free(expect);
	return (TEST_END(res));
}

int	test_dq_env_w_space(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], "ls -l", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = parse("\"$LS\"", g_env);
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line); test_line_free(expect);
	return (TEST_END(res));
}

int	test_sq_env(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], "$A", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = parse("\'$A\'", g_env);
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line); test_line_free(expect);
	return (TEST_END(res));
}

const t_test_function g_test_functions[] =
{
	test_single_cmd,
	test_cmd_with_arg,
    test_two_cmds,
	test_redir,
	test_env,
	test_double_quote,
	test_single_quote,
	test_dq_env,
	test_env_w_space,
	test_dq_env_w_space,
	test_sq_env,
    NULL
};

int main(int argc, char **argv)
{
	int	retval;

	g_env.vars = test_make_environ("A=a", "LS=ls -l", NULL);
	g_env.last_exit_status = 0;
	retval = test_main(argc, argv);
	test_free_environ(g_env.vars);
	(void)retval;
	return (0);
}
