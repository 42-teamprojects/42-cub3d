/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:49 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/15 15:33:18 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# define BRED "\e[1;31m"
# define CX "\033[0m"
# define BGREEN "\e[1;32m"
# define CYAN "\e[1;36m"

// Errors
# define ERR_CUB "Invalid map file (.cub)"
# define ERR_WALL "The map must be closed/surrounded by walls."
# define ERR_ARG "Please enter 1 map file as argument."
# define ERR_INFO "Invalid map information."
# define ERR_ELEMS "Map elements must be in the beginning of the file."
# define ERR_MAP "Invalid map."
# define ERR_RGB "Invalid RGB colors."
# define ERR_PLAYERS "There must be one player in the map."
// Game
# define TILE_SIZE 64
# define WIDTH 920
# define HEIGHT 800

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../mlx/include/MLX42/MLX42.h"

typedef struct s_info {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*_f;
	char	*_c;
	int		f[3];
	int		c[3];
	int		last;
}				t_info;

typedef struct s_map {
	t_info	*info;
	char	**map;
	int		width;
	int		height;
}				t_map;

typedef struct s_player {
	float	x;
	float	y;
	char	dir;
	float	angle;
	float 	fov;
}				t_player;

typedef struct s_imgs {
	mlx_image_t	*map;
	mlx_image_t	*player;
}				t_imgs;

typedef struct s_cords
{
	float x;
	float y;
}			t_cords;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	float	was_hit;
	float	is_up;
	float	is_down;
	float	is_left;
	float	is_right;
	float	wall_height;
	int		was_hit_vert;
}			t_ray;

typedef struct s_game {
	mlx_t		*mlx;
	t_map		*map;
	t_player	player;
	mlx_image_t	*img_map;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	int				*no_pxls;
	int				*so_pxls;
	int				*we_pxls;
	int				*ea_pxls;
}				t_game;

#endif