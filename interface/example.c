/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:12:03 by fjuras            #+#    #+#             */
/*   Updated: 2022/11/04 10:39:36 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "line.h"
#include "test_framework.h"

t_line	dummy_parser(const char * line_str)
{	
	t_line	line;
	int		i;

	(void)line_str;
	i = 0;
	test_line_init(&line, 2);
	test_prog_args(&line.progs[i], "ls", "-l", NULL);
	test_prog_redirs(&line.progs[i++], "in.txt", NULL);
	test_prog_args(&line.progs[i], "grep", "total", NULL);
	test_prog_redirs(&line.progs[i++], NULL, "out.txt");
	test_line_end(&line, i);
	return (line);
}

t_line simplest_parser(char *line_str)
{
	t_line	line;

	line.size = 1;
	line.progs = malloc(sizeof(t_prog));
	line.progs[0].args = calloc(2, sizeof(char *));
	line.progs[0].args[0] = strdup(line_str);
	line.progs[0].args[1] = NULL;
	line.progs[0].in_redir.path = NULL;
	line.progs[0].out_redir.path = NULL;
	return (line);
}

int	test_simplest(const char *filter)
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
	line = simplest_parser("ls");
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line);
	test_line_free(expect);
	return (TEST_END(res));
}

int	test_bit_harder(const char *filter)
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
	line = simplest_parser("grep total");
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line);
	test_line_free(expect);
	return (TEST_END(res));
}

int	test_dummy_passing(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 2);
	test_prog_args(&expect.progs[i], "ls", "-l", NULL);
	test_prog_redirs(&expect.progs[i++], "in.txt", NULL);
	test_prog_args(&expect.progs[i], "grep", "total", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, "out.txt");
	test_line_end(&expect, i);
	line = dummy_parser("<in.txt ls -l | grep total >out.txt");
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line);
	test_line_free(expect);
	return (TEST_END(res));
}

int	test_dummy_not_passing(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 3);
	test_prog_args(&expect.progs[i], "ls", "-l", NULL);
	test_prog_redirs(&expect.progs[i++], "in.txt", NULL);
	test_prog_args(&expect.progs[i], "grep", "total", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, "out.txt");
	test_prog_args(&expect.progs[i], "wc", "-l", NULL);
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = dummy_parser("<in.txt ls -l | grep total >out.txt");
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line);
	test_line_free(expect);
	return (TEST_END(res));
}

int	test_dummy_broken(const char *filter)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START(filter);
	i = 0;
	test_line_init(&expect, 3);
	test_prog_args(&expect.progs[i], "ls", "-l", NULL);
	test_prog_redirs(&expect.progs[i++], "in.txt", NULL);
	test_line_end(&expect, i);
	line = dummy_parser("<in.txt ls -l | grep total >out.txt");	
	res = test_expect_line_eq(&line, &expect);
	test_line_free(line);
	test_line_free(expect);
	return (TEST_END(res));
}

const t_test_function g_test_functions[] =
{
	test_simplest,
	test_bit_harder,
    test_dummy_not_passing,
    test_dummy_passing,
	// test_dummy_broken,
    NULL
};

int	main(int argc, char **argv)
{
	return (test_main(argc, argv));
}
