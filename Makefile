FILES_C = src/main.c src/comm.c src/chars.c src/read.c src/evs.c src/utils.c
FILES_O = main.o comm.o chars.o read.o evs.o utils.o
NAME = minishell
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@make -C libft/ all
	@cp libft/libft.a ./
	@make -C printf/ all
	@cp printf/libftprintf.a ./
	@echo "\033[0;5;33mCompiling and building\033[0m"
	@gcc -c $(FLAGS) $(FILES_C) -I ./includes
	@gcc -o $(NAME) $(FLAGS) $(FILES_O) -I ./includes -L . -lftprintf
	@echo "\033[0;32mFinished building \033[40;97m$(NAME)\033[0m"

clean:
	@/bin/rm -f $(FILES_O)
	@make -C libft/ clean
	@make -C printf/ clean

fclean:
	@/bin/rm -f $(FILES_O)
	@/bin/rm -f $(NAME)
	@/bin/rm -f libft.a
	@/bin/rm -f libftprintf.a
	@make -C libft/ fclean
	@make -C printf/ fclean

re:	fclean all

retest:
	@echo "\033[0;34mRemaking for test\033[0m"
	@rm $(NAME)
	@gcc -c $(FLAGS) $(FILES_C) -I ./includes
	@gcc -o $(NAME) $(FLAGS) $(FILES_O) -I ./includes -L . -lftprintf
