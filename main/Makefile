NAME = minishell

FILES = \
	main utils

HEADERS = \
	../interface/line ../interface/env

HFILES += $(HEADERS:%=%.h)
OFILES = $(FILES:%=%.o)
CFLAGS = -Wall -Wextra -Werror
OPTIM = -ggdb3
export OPTIM
INC = -I..
LIBS= -lexecutor -lparser -lft -lreadline
LIBS_FILES_ = executor/libexecutor.a parser/libparser.a libft/libft.a
LIBS_FILES = $(addprefix ../, $(LIBS_FILES_))
LIBS_DIRS = $(addprefix -L, $(dir $(LIBS_FILES)))

all: $(NAME)

$(NAME): $(OFILES) $(LIBS_FILES)
	gcc $(LIBS_DIRS) $(OFILES) $(LIBS) -o $@

$(OFILES): %.o: %.c $(HFILES)
	gcc $(CFLAGS) $(OPTIM) $(INC) -c $< -o $@

../executor/libexecutor.a: FORCE
	make -C ../executor

../parser/libparser.a: FORCE
	make -C ../parser

../libft/libft.a: FORCE
	make -C ../libft

FORCE: ;

clean_:
	rm -f $(OFILES)

clean: clean_libs clean_

fclean_: clean_
	rm -f $(NAME)

fclean: fclean_ clean
	rm -f $(LIBS_FILES)

re_: fclean_ all

re: re_libs re_

clean_libs:
	make clean -C ../libft
	make clean -C ../executor
	make clean -C ../parser

re_libs:
	make re -C ../libft
	make re -C ../executor
	make re -C ../parser

.PHONY: all clean clean_ fclean fclean_ re re_ re_libs clean_libs FORCE
