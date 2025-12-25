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

LIBPATH := -L$(LIBFT_DIR) -L$(MLX_DIR)
LIBS := -lft -l$(MLX_LIB_NAME) $(MLX_FLAGS)

INCLUDES := -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

SRCS := $(SRC_DIR)/camera.c \
				$(SRC_DIR)/color.c \
				$(SRC_DIR)/error_utils.c \
				$(SRC_DIR)/hit_record.c \
				$(SRC_DIR)/main.c \
				$(SRC_DIR)/material.c \
				$(SRC_DIR)/math_utils.c \
				$(SRC_DIR)/minilibx_utils.c \
				$(SRC_DIR)/object_list.c \
				$(SRC_DIR)/random_number_generator.c \
				$(SRC_DIR)/ray.c \
				$(SRC_DIR)/sphere.c \
				$(SRC_DIR)/plane.c \
				$(SRC_DIR)/cylinder.c \
				$(SRC_DIR)/utilities.c \
				$(SRC_DIR)/vec3_basic.c \
				$(SRC_DIR)/vec3_basic2.c \
				$(SRC_DIR)/vec3_random.c \
				$(SRC_DIR)/vec3_physics.c \
				$(SRC_DIR)/vec3_utils.c \
				$(SRC_DIR)/light.c \
				$(SRC_DIR)/calculate_color.c \
				$(SRC_DIR)/ft_atof.c \
				$(SRC_DIR)/parse.c \
				$(SRC_DIR)/parse_line.c \
				$(SRC_DIR)/parse_utils.c


OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBPATH) $(LIBS) -o $(NAME)

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
