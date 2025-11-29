# Variables
NAME := miniRT
SRC_DIR := src

CC := cc
RM := rm -f
RMDIR := rm -rf

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
MLX_DIR := minilibx
MLX := $(MLX_DIR)/libmlx.a
LIBPATH := -L$(MLX_DIR) -L$(LIBFt_DIR)
LIBS := -lft -lmlx_Linux -lm -lXext -lX11

INCLUDE_DIR := include
INCLUDES := -I$(INCLUDE_DIR)
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
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(LIBPATH) $(FRAMEWORK) $(OBJS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RMDIR) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) fclean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
