NAME = libparser.a

FILES = \
	ft_split_argc ft_strjoin_char parse_set_quotes \
	parse parse_int replace_util replace cmd utils \
	translate translate_redir

HFILES = parser.h struct.h ../interface/line.h

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
	genhtml cov.info --output-directory ../parser-cov

.PHONY: all clean fclean re
