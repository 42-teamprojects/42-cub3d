/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:49 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/03 18:55:17 by yelaissa         ###   ########.fr       */
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
// Game
# define TILE_SIZE 64

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
	int		x;
	int		y;
	char	dir;
}				t_player;

typedef struct s_game {
	mlx_t		*mlx;
	t_map		*map;
	t_player	*player;
}				t_game;

#endif