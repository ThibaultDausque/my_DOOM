CC = cc
CFLAGS = -Wall -Wextra -Werror -g
BIN = bin
SRC = src
SRCS = src/main.c src/get_map_line.c
INCLUDES = -Iincludes
OBJS = $(SRCS:src/%.c=$(BIN)/%.o)
FLAGS = -Wall -Wextra -Werror -g
OS = $(shell uname -s)

NAME = doom

all:$(NAME)

ifeq ($(OS), Linux)
$(BIN)/%.o: $(SRC)/%.c
	@mkdir -p $(BIN)
	$(CC) $(FLAGS) $(INCLUDES) -Imlx_linux -c $< -o $@
$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -L/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
else
$(OBJS)/%.o: src/%.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
endif

# $(OBJS)/%.o: %.c
# 	@cd lib/minilibx_linux && make -s

clean:
	rm -rf bin

fclean: clean
	rm -f $(NAME)

re:
	fclean all

.PHONY: clean fclean all macos linux