CC = cc
CFLAGS = -Wall -Wextra -Werror
BIN = bin
SRCS = src/main.c
INCLUDES = -Idoom.h -Ilib/SDL/include/SDL3
OBJS = $(SRC:%.c=$(BIN)/%.o)

NAME = doom

all:$(NAME)


