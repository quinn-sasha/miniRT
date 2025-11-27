# Variables
NAME := miniRT
SRC_DIR := src

CC := cc
RM := rm -f
RMDIR := rm -rf

MLX_DIR := minilibx
MLX := $(MLX_DIR)/libmlx.a
GET_NEXT_LINE_DIR := get_next_line
GET_NEXT_LINE := $(GET_NEXT_LINE_DIR)/libget_next_line.a
LIBPATH := -L$(MLX_DIR) -L$(GET_NEXT_LINE_DIR)
LIBS := -lget_next_line -lmlx_Linux -lm -lXext -lX11

INCLUDE_DIR := include
INCLUDES := -I$(INCLUDE_DIR) -I$(MLX_DIR)
CFLAGS := -Wall -Wextra -Werror

# TODO
SRCS := 

OBJ_DIR := objs
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Platform compatibility

UNAME := $(shell uname -s)

# arm
ifeq ($(UNAME),arm)
	FRAMEWORK := -framework OpenGL -framework AppKit
endif

# General rules
all: $(NAME) $(MLX)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(LIBPATH) $(FRAMEWORK) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(RMDIR) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
