/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:12:03 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/02 21:12:43 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <interface/env.h>
#include <interface/line.h>
#include <test_framework/test_framework.h>
#include <parser/parser.h>

t_env	g_env;

#define check_variant(...) check_variant_x(__FILE__, __LINE__, __VA_ARGS__)
int	check_variant_x(const char *from, int line, t_env env, t_line exp, char *input)
{
	t_line	parsed_line;
	int		r;

	parsed_line = parse(input, env);
	r = test_expect_line_eq_x(from, line, &parsed_line, &exp);
	test_line_free(parsed_line);
	return (r);
}

int	test_framework_leak(const char *filter)
{
	t_line	exp;
	int		i;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 2);
	test_prog_args(&exp.progs[i], "ls", "-l", NULL);
	test_prog_redirs(&exp.progs[i++], "in.txt", NULL);
	test_prog_args(&exp.progs[i], "grep", "total", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, "out.txt");
	test_line_end(&exp, i);
	test_line_free(exp);
	return (TEST_END(1));
}

int	test_single_cmd(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "ls", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "ls") &&
		check_variant(g_env, exp, " ls ");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_cmd_with_arg(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "grep", "total", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "grep total");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_two_cmds(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 2);
	test_prog_args(&exp.progs[i], "ls", "-l", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_prog_args(&exp.progs[i], "grep", "total", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "ls -l | grep total") &
		check_variant(g_env, exp, "ls -l|grep total");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_redir_simple(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "ls", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, "out.txt");
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "ls >out.txt")&&
		check_variant(g_env, exp, ">out.txt ls");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_redir(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "ls", NULL);
	test_prog_redirs(&exp.progs[i++], "in.txt", "out.txt");
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "<in.txt ls >out.txt") &&
		check_variant(g_env, exp, "ls <in.txt >out.txt") &&
		check_variant(g_env, exp, "<in.txt >out.txt ls") &&
		check_variant(g_env, exp, ">out.txt ls <in.txt") &&
		check_variant(g_env, exp, ">out.txt <in.txt ls") &&
		check_variant(g_env, exp, "ls >out.txt <in.txt");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_alt_redir(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "ls", NULL);
	test_prog_redirs(&exp.progs[i], "in.txt", "out.txt");
	exp.progs[i].in_redir.is_alt = 1;
	exp.progs[i++].out_redir.is_alt = 1;
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "<<in.txt ls >>out.txt") &&
		check_variant(g_env, exp, "<< in.txt ls >> out.txt");
	test_line_free(exp);
	return (TEST_END(r));
}


int	test_duplicate_redir(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "ls", NULL);
	test_prog_redirs(&exp.progs[i], NULL, "other.txt");
	exp.progs[i++].out_redir.is_alt = 1;
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, ">out.txt ls >>other.txt");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_env(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "a", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "$A");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_env_in_string(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "tralabala", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "tr$Al$A$B$Al$A");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_env_exit_status(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	g_env.last_exit_status = 42;
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "echo", "42", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "echo $?");
	test_line_free(exp);
	g_env.last_exit_status = 0;
	return (TEST_END(r));
}

int	test_env_not_existing(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	g_env.last_exit_status = 42;
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "echo", "", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "echo $RANDOM_BASH");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_env_lone_dollar(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	g_env.last_exit_status = 42;
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "echo", "$", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "echo $");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_double_quote(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "one string", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "\"one string\"");
	test_line_free(exp);
	return (TEST_END(r));
}


int	test_single_quote(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "one string", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "\'one string\'");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_dq_env(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "a", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "\"$A\"");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_env_w_space(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "ls", "-l", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "$LS");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_dq_env_w_space(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "ls -l", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "\"$LS\"");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_sq_env(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "$A", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "\'$A\'");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_many_quotes(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 1);
	test_prog_args(&exp.progs[i], "ab\'c\"d", NULL);
	test_prog_redirs(&exp.progs[i++], NULL, NULL);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "\"a\"\'b\'\"\'\"c\'\"\'\"\"\'\'d");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_empty_input(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 0);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "") &
		check_variant(g_env, exp, "   ");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_invalid_input_empty_cmd(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 0);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "|") &
		check_variant(g_env, exp, "ls |") &
		check_variant(g_env, exp, "| ls") &
		check_variant(g_env, exp, "ls | | grep") &
		check_variant(g_env, exp, "ls || grep") &
		check_variant(g_env, exp, "  | ls") &
		check_variant(g_env, exp, "ls |   ");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_invalid_input_forbidden_char(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 0);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "echo ; cat") &
		check_variant(g_env, exp, "echo lol\\n");
	test_line_free(exp);
	return (TEST_END(r));
}

int	test_invalid_input_unclosed_quote(const char *filter)
{
	t_line	exp;
	int		i, r;

	TEST_START(filter);
	i = 0;
	test_line_init(&exp, 0);
	test_line_end(&exp, i);
	r = check_variant(g_env, exp, "echo \'yolo") &
		check_variant(g_env, exp, "echo \"sfag");
	test_line_free(exp);
	return (TEST_END(r));
}

const t_test_function g_test_functions[] =
{
	test_framework_leak,
	test_single_cmd,
	test_cmd_with_arg,
    test_two_cmds,
	test_redir_simple,
	test_redir,
	test_alt_redir,
	test_duplicate_redir,
	test_env,
	test_env_in_string,
	test_env_exit_status,
	test_env_not_existing,
	test_env_lone_dollar,
	test_double_quote,
	test_single_quote,
	test_dq_env,
	// test_env_w_space,
	test_dq_env_w_space,
	test_sq_env,
	test_many_quotes,
	test_empty_input,
	test_invalid_input_empty_cmd,
	test_invalid_input_forbidden_char,
	test_invalid_input_unclosed_quote,
    NULL
};

int main(int argc, char **argv)
{
	int	retval;

	g_env.vars = test_make_environ("A=a", "B=b", "LS=ls -l", NULL);
	g_env.last_exit_status = 0;
	retval = test_main(argc, argv);
	test_free_environ(g_env.vars);
	(void)retval;
	return (0);
}
