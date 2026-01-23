CC = cc
CFLAGS = -Wall -Wextra -Werror -g
BIN = bin
SRC = src
SRCS = src/main.c src/utils.c src/raycasting.c
INCLUDES = -Iincludes -Ilib/minilibx-linux
OBJS = $(SRCS:src/%.c=$(BIN)/%.o)
OS = $(shell uname -s)

NAME = doom

all:$(NAME)

ifeq ($(OS), Linux)
$(BIN)/%.o: $(SRC)/%.c
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
$(NAME): $(OBJS)
	@cd lib/minilibx-linux && make
	@$(CC) $(CFLAGS) $(OBJS) -Llib/minilibx-linux -lmlx -lXext -lX11 -lm -lz -o $(NAME)
else
$(OBJS)/%.o: src/%.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@ && cd lib/minilibx-linux && make
$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
endif


clean:
	rm -rf bin

fclean: clean
	@cd lib/minilibx-linux && make clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all macos linux