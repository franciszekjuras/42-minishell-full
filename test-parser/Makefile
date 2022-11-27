NAME = test

FILES = \
	test

HEADERS = \
	../interface/line ../interface/test_framework

HFILES += $(HEADERS:%=%.h)
OFILES = $(FILES:%=%.o)
CFLAGS = -Wall -Wextra -Werror
OPTIM = -ggdb3
export OPTIM
INC = -I..
LIBS= -lparser -lft -lgcov --coverage
LIBS_FILES_ = parser/libparser.a libft/libft.a
LIBS_FILES = $(addprefix ../, $(LIBS_FILES_))
LIBS_DIRS = $(addprefix -L, $(dir $(LIBS_FILES)))

all: $(NAME)

$(NAME): $(OFILES) $(LIBS_FILES)
	gcc $(LIBS_DIRS) $(OFILES) $(LIBS) -o $@

$(OFILES): %.o: %.c $(HFILES)
	gcc $(CFLAGS) $(OPTIM) $(INC) -c $< -o $@

$(LIBS_FILES): FORCE
	make -C ../libft
	make -C ../parser

FORCE: ;

clean_:
	rm -f $(OFILES) $(OFILES2)

clean: clean_libs clean_

fclean_: clean_
	rm -f $(NAME)

fclean: fclean_ clean
	rm -f $(LIBS_FILES)

re_: fclean_ all

re: re_libs re_

clean_libs:
	make clean -C ../libft
	make clean -C ../parser

re_libs:
	make re -C ../libft
	make re -C ../parser

libs_cov_:
	make -C ../libft
	make re -C ../parser COV_FLAGS="-fprofile-arcs -ftest-coverage"

cov: libs_cov_ all
	./test
	make -C ../parser report
	make -C ../parser fclean

.PHONY: all clean clean_ cov fclean fclean_ re re_ re_libs clean_libs FORCE
