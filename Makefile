# Variables
NAME := miniRT
SRC_DIR := src
OBJ_DIR := objs
LIBFT_DIR := libft
MLX_DIR := minilibx
INCLUDE_DIR := include

CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
RMDIR := rm -rf

# -- Platform compatibility -----------
UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
    MLX_LIB_NAME := mlx_Linux
    MLX_FILE := libmlx_Linux.a
    MLX_FLAGS := -lXext -lX11 -lm
else
    MLX_LIB_NAME := mlx
    MLX_FILE := libmlx.a
    MLX_FLAGS := -framework OpenGL -framework AppKit -lm
endif
# ------------------------------------

LIBFT := $(LIBFT_DIR)/libft.a
MLX := $(MLX_DIR)/$(MLX_FILE)

LIBPATH := -L$(MLX_DIR) -L$(LIBFT_DIR)
LIBS := -lft -l$(MLX_LIB_NAME) $(MLX_FLAGS)

INCLUDES := -I$(INCLUDE_DIR) -I$(MLX_DIR)

SRCS := $(SRC_DIR)/vec3.c \
        $(SRC_DIR)/main.c \

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBPATH) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RMDIR) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean 

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
