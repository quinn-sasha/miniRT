NAME = libget_next_line.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = get_next_line.c
OBJ = $(SRC:%.c=%.o)
LIBFTDIR = ../libft
LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
