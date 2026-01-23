CC = cc
CFLAGS = -Wall -Wextra -Werror -g
BIN = bin
SRC = src
SRCS = src/main.c src/utils.c src/raycasting.c
INCLUDES = -Iincludes -Ilib/minilibx-linux
INCLUDES_MAC0S = -Iincludes -Ilib/minilibx_macos_opengl/minilibx_opengl_20191021
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
$(BIN)/%.o: $(SRC)/%.c
	@mkdir -p $(BIN)
	$(CC) $(INCLUDES_MAC0S) -c $< -o $@
$(NAME): $(OBJS)
	@cd lib/minilibx_macos_opengl/minilibx_opengl_20191021 && make
	$(CC) $(OBJS) -Llib/minilibx_macos_opengl/minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit -o $(NAME)
endif


clean:
	rm -rf bin

fclean: clean
	@cd lib/minilibx-linux && make clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all macos linux
