NAME = libexecutor.a

FILES = \
	executor exec_data childs app app_priv utils \
	builtins lineops envops var_utils\

HFILES := $(FILES:%=%.h)

HFILES += ../interface/line.h

FILES += \
	app_priv2 envops2 builtins2 builtins3

OFILES := $(FILES:%=%.o)

CFLAGS = -Wall -Wextra -Werror

INC = -I..

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $@ $?

$(OFILES): %.o: %.c $(HFILES)
	gcc $(CFLAGS) $(COV_FLAGS) $(OPTIM) $(INC) -c $< -o $@

clean_cov:
	rm -f $(FILES:%=%.gcda)
	rm -f $(FILES:%=%.gcno)
	rm -f cov.info
	rm -rf out/

clean: clean_cov
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

report:
	lcov -c --directory . --output-file cov.info
	genhtml cov.info --output-directory ../executor-cov

.PHONY: all clean fclean re
