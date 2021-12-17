# --MAKEFILE--

NAME = minishell
HEADERS = test.h\
			parser.h\

FLAGS = -Wall -Wextra -Werror -lreadline
SOURCES = main.c\
			parser.c\
			pwd.c\
			parser_ut1.c\
			parser_ut2.c\
			
OBJECTS = $(SOURCES:.c=.o)
LIBS = -L./lib/libft -L./lib/ft_printf -lft -lftprintf 

all: $(NAME)

libraries :
	cd ./lib/libft; make;
	cd ./lib/ft_printf; make;

$(NAME) : $(OBJECTS) | libraries
	gcc $(FLAGS) $(OBJECTS) $(LIBS) -o $(NAME)
	@echo "\033[34mcompiled successfully\033[0m"

clean:
	@rm -rf $(NAME) $(OBJECTS)
	@echo "\033[33mclean completed\033[0m"


fclean: clean
	@make fclean -C ./lib/libft
	@make fclean -C ./lib/ft_printf

re: fclean all
