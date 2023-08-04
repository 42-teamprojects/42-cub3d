NAME = cub3D

LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -I includes/ -fsanitize=address -g

CC = cc

HEADERS = includes/global.h includes/cub3d.h

MLX42 = mlx/build/libmlx42.a

GLFW = $(shell brew --prefix glfw)

DEPS = -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L"$(GLFW)/lib" $(MLX42)

SRCS = main.c \
	sources/parser/parser.c \
	sources/parser/map_get.c \
	sources/parser/map_check.c \
	sources/parser/map_info.c \
	sources/parser/map_utils.c \
	sources/raycasting/raycasting.c \
	sources/utils/utils.c \
	sources/utils/clean.c \
	sources/raycasting/draw_map.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(DEPS) $(LIBFT)
	@echo "Compilation done"

$(LIBFT):
	@make all -C libft

clean:
	@rm -f $(OBJS)
	@echo "Cleaning done"

fclean: clean
	@rm -f $(NAME) $(LIBFT)
	@echo "Full cleaning done"

re: fclean all

# to be deleted
run: all
	@./cub3D maps/1.cub

test: tedt.c 
	@$(CC)  tedt.c -o test $(DEPS) && ./test
	@echo "Compilation done"