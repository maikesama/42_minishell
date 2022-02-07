# --MAKEFILE--

NAME = minishell
SRCDIR = src
OBJDIR = obj
INCDIR = headers

HEADERS = $(shell find $(INCDIR) -name "*.h")

SOURCES = $(shell find $(SRCDIR) -name "*.c")

OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LIBS = -L./lib/libft -L./lib/ft_printf -lft -lftprintf -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include -lreadline

#MACOS_INC = -I$(HOME)/homebrew/opt/readline/include
#MACOS_LIB = -L$(HOME)/homebrew/opt/readline/lib 
# /Users/pceccoli/.brew/Cellar/readline/8.1.2
all: $(NAME)

libraries :
	@make -C ./lib/libft
	@make -C ./lib/ft_printf

$(NAME) :$(OBJECTS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "\033[32m"$@" compiled successfully\033[0m"

$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADERS) | libraries
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[34m"$<" compiled successfully\033[0m"

clean:
	@rm -rf $(NAME) $(OBJECTS)
	@echo "\033[33m"$(NAME)" clean completed\033[0m"


fclean: clean
	@make fclean -C ./lib/libft
	@make fclean -C ./lib/ft_printf
	@rm -rf $(OBJDIR)
	@echo "\033[33mfull clean completed\033[0m"

re: fclean all