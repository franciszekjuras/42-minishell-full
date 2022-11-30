#ifndef TEST_LINE_H
# define TEST_LINE_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include "line.h"

# define TEST_FILTER(filter) \
do { \
if (filter != NULL && strncmp(__func__, filter, strlen(filter)) != 0) \
	return (-1); \
} while(0)

# define TEST_START_CLEAN(filter) {TEST_FILTER(filter); test_start_clean(__func__);}
# define TEST_START(filter) {TEST_FILTER(filter); test_start(__func__);}
# define TEST_END(res) test_end(__func__, (res))

# define TEST_STR_RUN "\e[1;36m[RUN   ]\e[m"
# define TEST_STR_OK "\e[1;32m[    OK]\e[m"
# define TEST_STR_FAIL "\e[1;31m[  FAIL]\e[m"
# define TEST_DIF_PLUS "\e[32m+ %s\n\e[m"
# define TEST_DIF_MINUS "\e[31m- %s\n\e[m"
# define TEST_FILE_LINE "\e[36m%s:%d\e[m"
# define TEST_FILE "\e[36m%s\e[m"
# define TEST_FROM ">>> \e[33m%s:%d\e[m\n"
# define TEST_NONL "\\ No newline at end of file"
# define TEST_BOLD(x) "\e[1m" x "\e[m"

typedef int (*t_test_function)(const char *);
extern const t_test_function g_test_functions[];

int test_remove_files_from_dir(char *dir_path)
{
	DIR				*dir;
	struct dirent	*next_file;
	char			filepath[1024];

	dir = opendir(dir_path);
	while ( (next_file = readdir(dir)) != NULL )
	{
		if (strcmp(next_file->d_name, ".") != 0 && strcmp(next_file->d_name, "..") != 0)
		{
			sprintf(filepath, "%s/%s", dir_path, next_file->d_name);
			remove(filepath);
		}
	}
	closedir(dir);
	return 0;
}

void	test_strarr_free(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i] != 0)
		free(strarr[i++]);
	free(strarr);
}

void	test_line_free(t_line line)
{
	int		i;
	t_prog	*prog;

	i = 0;
	while (i < line.size)
	{
		prog = &line.progs[i];
		test_strarr_free(prog->args);
		free(prog->in_redir.path);
		free(prog->out_redir.path);
		++i;
	}
	free(line.progs);
}

void	test_update_results(int test_result, int *passed, int *total)
{
	if (test_result < 0)
		return ;
	(*total)++;
	if (test_result)
		(*passed)++;
}

void	test_printarr(char **arr, char *sep)
{
	int	i;
	int	n;

	n = 0;
	while (arr[n] != NULL)
		++n;
	i = 0;
	while (i < n)
	{
		fprintf(stderr, "%s", arr[i]);
		if (i + 1 < n)
			fprintf(stderr, "%s", sep);
		++i;
	}
}

void	test_line_print(const t_line *line)
{
	int		i;
	t_prog	*prog;

	i = 0;
	while (i < line->size)
	{
		prog = &line->progs[i];
		if (prog->in_redir.path != NULL)
			fprintf(stderr, "\e[1;33m%s\e[m%s ",
				prog->in_redir.is_alt ? "<<" : "<", prog->in_redir.path);
		test_printarr(prog->args, "\e[1;30m·\e[m");
		if (prog->out_redir.path != NULL)
			fprintf(stderr, " \e[1;36m%s\e[m%s",
				prog->out_redir.is_alt ? ">>" : ">", prog->out_redir.path);
		if (i + 1 < line->size)
			fprintf(stderr, " | ");
		++i;
	}
	fprintf(stderr, "\n");
}


int	test_strarr_eq(char **actual, char **expected)
{
	int	i;

	i = 0;
	while (actual[i] != NULL && expected[i] != NULL)
	{
		if (strcmp(actual[i], expected[i]) != 0)
			return (0);
		++i;
	}
	return (actual[i] == expected[i]);
}

int	test_redir_eq(t_redir *actual, t_redir *expected)
{	
	if (actual->path == NULL || expected->path == NULL)
		return (actual->path == expected->path);
	else
		return (strcmp(actual->path, expected->path) == 0 &&
			actual->is_alt == expected->is_alt);
}

int	test_prog_eq(t_prog *actual, t_prog *expected)
{
	if (!test_redir_eq(&actual->in_redir, &expected->in_redir))
		return (0);
	if (!test_redir_eq(&actual->out_redir, &expected->out_redir))
		return (0);
	if (!test_strarr_eq(actual->args, expected->args))
		return (0);
	return (1);
}

int	test_line_eq(t_line *actual, t_line *expected)
{
	int	i;

	if (actual->size != expected->size)
		return (0);
	i = 0;
	while (i < actual->size)
	{
		if (!test_prog_eq(&actual->progs[i], &expected->progs[i]))
			return (0);
		++i;
	}
	return (1);
}

#define test_expect_line_eq(...) test_expect_line_eq_x(__FILE__, __LINE__, __VA_ARGS__)
int	test_expect_line_eq_x(const char *from, int line, t_line *actual, t_line *expected)
{
	int	eq;

	eq = test_line_eq(actual, expected);
	if (!eq)
	{
		fprintf(stderr, TEST_FROM, from, line);
		fprintf(stderr, "Lines don't match:\n");
		fprintf(stderr, "Actual  : ");
		test_line_print(actual);
		fprintf(stderr, "Expected: ");
		test_line_print(expected);
	}
	return (eq);
}


#define test_expect_retval(...) test_expect_retval_x(__FILE__, __LINE__, __VA_ARGS__)
int	test_expect_retval_x(const char *from, int line, int actual, int expected)
{
	if (actual != expected)
	{
		fprintf(stderr, TEST_FROM, from, line);
		fprintf(stderr, "Return value does not match:\n");
		fprintf(stderr, "Actual  : %d\n", actual);
		fprintf(stderr, "Expected: %d\n", expected);
	}
	return (actual == expected);
}

char *test_getline(FILE *file)
{
	char *line;
	ssize_t size;
	size_t	n;

	line = NULL;
	n = 0;
	size = getline(&line, &n, file);
	if (size < 0)
	{
		free(line);
		return (NULL);
	}
	if (line[size - 1] == '\n')
		line[size - 1] = '\0';
	return (line);
}

const char	*null_to_eof(const char *str)
{
	if (str == NULL)
		return ("EOF");
	else
		return (str);
}

#define test_expect_file_size(...) test_expect_file_size_x(__FILE__, __LINE__, __VA_ARGS__)
int	test_expect_file_size_x(const char *from, int line, const char *filename, long size)
{
	struct stat	st;

	if (stat(filename, &st) < 0)
	{
		fprintf(stderr, TEST_FROM TEST_FILE ": %s\n",
			from, line, filename, strerror(errno));
		return (0);
	}
	if (st.st_size != size)
	{
		fprintf(stderr, TEST_FROM, from, line);
		fprintf(stderr, TEST_FILE " size does not match:\n", filename);
		fprintf(stderr, "Actual  : %ld\n", st.st_size);
		fprintf(stderr, "Expected: %ld\n", size);
		return (0);
	}
	else
		return (1);
}

#define test_expect_file_content(...) test_expect_file_content_x(__FILE__, __LINE__, __VA_ARGS__)
int	test_expect_file_content_x(const char *from, int line, const char *filename, ...)
{
	va_list vargs;
	char	*refline;
	char	*actline;
	FILE	*file;
	int		i;
	int		full_match;
	int		lines_differ;

	full_match = 0;
	lines_differ = 0;
	file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, TEST_FROM TEST_FILE ": %s\n",
			from, line, filename, strerror(errno));
		return (0);
	}
	i = 1;
	va_start(vargs, filename);
	while (!lines_differ && !full_match)
	{
		refline = va_arg(vargs, char*);
		actline = test_getline(file);
		if (refline == NULL || actline == NULL)
		{
			if (refline == actline)
				full_match = 1;
			else
				lines_differ = 1;
		}
		else if (strcmp(refline, actline) != 0)
			lines_differ = 1;
		if (lines_differ)
			fprintf(stderr, TEST_FROM TEST_FILE_LINE " does not match expected output\n"
				TEST_DIF_PLUS TEST_DIF_MINUS,
				from, line, filename, i, null_to_eof(actline), null_to_eof(refline));
		++i;
		free(actline);
	}
	va_end(vargs);
	fclose(file);
	return (full_match);
}

char	**test_make_environ(char *first, ...)
{
	int		i;
	va_list vargs;
	int		size;
	char	*var;
	char	**environ;

	size = 0;
	va_start(vargs, first);
	var = first;
	while (var != NULL)
	{
		var = va_arg(vargs, char*);
		++size;
	}
	va_end(vargs);
	environ = calloc(size + 1, sizeof(char *));
	environ[size] = NULL;
	va_start(vargs, first);
	i = 0;
	var = first;
	while (i < size)
	{
		environ[i] = strdup(var);
		var = va_arg(vargs, char*);
		++i;
	}
	va_end(vargs);
	return (environ);
}

void	test_free_environ(char **env)
{
	test_strarr_free(env);
}

void	test_prog_args(t_prog *prog, ...)
{
	int		i;
	va_list vargs;
	int		size;

	size = 0;
	va_start(vargs, prog);
	while (va_arg(vargs, char*) != NULL)
		++size;
	va_end(vargs);
	prog->args = calloc(size + 1, sizeof(char *));
	prog->args[size] = NULL;
	va_start(vargs, prog);
	i = 0;
	while (i < size)
		prog->args[i++] = strdup(va_arg(vargs, char*));
	va_end(vargs);
}

void	test_prog_redirs(t_prog *prog, const char *in, const char *out)
{
	if (in != NULL)
		prog->in_redir.path = strdup(in);
	else
		prog->in_redir.path = NULL;
	if (out != NULL)
		prog->out_redir.path = strdup(out);
	else
		prog->out_redir.path = NULL;
	prog->in_redir.is_alt = 0;
	prog->out_redir.is_alt = 0;
}

void	test_line_init(t_line *line, int size)
{
	line->size = size;
	line->progs = calloc(size, sizeof(t_prog));
}

void	test_line_end(t_line *line, int it)
{
	if (line->size != it)
	{
		fprintf(stderr, "Error: Number of initialized line->progs (%d)"
			" doesn't match line->size (%d)\n",
			it, line->size);
		exit(1);
	}
}

char	**test_get_cwd_var(void)
{
	static char	*cwd;

	return (&cwd);
}

void	test_store_cwd(void)
{
	*test_get_cwd_var() = getcwd(NULL, 0);
}

void 	test_restore_cwd(void)
{
	chdir(*test_get_cwd_var());
	free(*test_get_cwd_var());
}

void	test_redirect_stdout(const char *filename)
{
	int	redir_fd;

	redir_fd = creat(filename, 0644);
	if (redir_fd < 0)
	{
		fprintf(stderr, "%s: %s\n", filename, strerror(errno));
		exit(1);
	}
	dup2(redir_fd, 1);
	if (redir_fd != 1)
		close(redir_fd);
}

void	test_close_stdout()
{
	close(1);
}


int	*test_get_stdin_fd(void)
{
	static int	stdin_fd;

	return (&stdin_fd);
}

void	test_redirect_stdin(const char *filename)
{
	int	redir_fd;

	redir_fd = open(filename, O_RDONLY);
	if (redir_fd < 0)
	{
		fprintf(stderr, "%s: %s\n", filename, strerror(errno));
		exit(1);
	}
	*test_get_stdin_fd() = dup(0);
	dup2(redir_fd, 0);
	if (redir_fd != 0)
		close(redir_fd);
}

void	test_restore_stdin()
{
	dup2(*test_get_stdin_fd(), 0);
	if (*test_get_stdin_fd() != 0)
		close(*test_get_stdin_fd());
	*test_get_stdin_fd() = 0;
}

void	test_start(const char *test_name)
{
	fprintf(stderr, "%s %s\n", TEST_STR_RUN, test_name);
}

void	test_start_clean(const char *test_name)
{
	test_start(test_name);
	test_remove_files_from_dir("out");
}

int	test_end(const char *test_name, int success)
{
	if (success)
		fprintf(stderr, "%s %s\n", TEST_STR_OK, test_name);
	else
		fprintf(stderr, "%s %s\n", TEST_STR_FAIL, test_name);
	return (success);
}

int	test_main(int argc, char **argv)
{
	char	*filter;
	int		passed;
	int		total;
	int		i;

	if (argc == 2)
		filter = argv[1];
	else
		filter = NULL;
	passed = 0;
	total = 0;
	i = 0;
	while (g_test_functions[i] != NULL)
		test_update_results(g_test_functions[i++](filter),
			&passed, &total);
	fprintf(stderr, "----\n");
	if (passed == total)
		fprintf(stderr, "    %s " TEST_BOLD("all %d tests passed\n"), TEST_STR_OK, total);
	else
		fprintf(stderr, "    %s " TEST_BOLD("%d of %d tests failed\n"), TEST_STR_FAIL,
			total - passed, total);
	fprintf(stderr, "----\n");
	close(0);
	close(1);
	close(2);
	return (passed < total);
}

#endif