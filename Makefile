NAME	:= fdf
#CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3
CFLAGS	:= -g3 -O0 -Wextra -Wall -Werror
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
SRCS	:= $(addprefix ./src/mandatory/, 1_main.c 2_init.c 3_init_map.c \
		4_init_map_utils.c 5_init_position.c 6_randomize.c 7_scale.c 8_rotation.c \
		9_translation.c 10_bresenham.c 11_hooks.c 12_utils.c)
OBJS	:= ${SRCS:.c=.o}

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean

re: clean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRC) $(BONUS_SRC) libft.h

.PHONY: all, clean, fclean, re, libmlx, libft