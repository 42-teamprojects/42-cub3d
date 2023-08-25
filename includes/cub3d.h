/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:07:29 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/25 17:48:23 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "global.h"

t_game	*g_game;

// Parser
t_map	*parser(char *file);
t_map	*get_map(char *file);
t_map	*check_map(char **map);
// // Map
int		found_info(t_info *info);
int		is_all_wall(char *line);
int		find_info(char *line, t_info *info);
t_info	*check_infos(char **map);
int		valid_info(t_info **info);
void	save_player_info(int i, int j, char dir);
int		count_cols(char **map);
int		is_valid_elements(char **map);
int		is_one_wnse(char **map);
int		is_surrounded(char **map);
int		check_file(char *file, int *fd);
int		check_newline(int *map_start, int *map_end, char *line, int i);
char	*read_map(int fd);
int		valid_map(char **map, int *cols, int *rows);
t_map	*check_map(char **map);

// Game
int		init_game(char *file);
void	reverse_array(int *arr, int len);

// Utils
void	throw_err(char *err);
void	free_arr(char **arr);
int		ft_arrlen(char **arr);
char	**ft_arrdup(char **arr);
// Clean up
void	free_game(t_game *game);
void	free_map(t_map *map);
void	free_info(t_info *info);

// get_raying

void	ft_hook(void *param);
void	cast_ray(void);
int		get_rgba(int r, int g, int b, float a);
float	normalize_angle(float rayAngle);
t_ray	get_ray(float ray_angle);
float	distance_between_points(float x1, float y1, float x2, float y2);
void	draw_texture(t_ray ray, t_cords param, float wall_height);
t_ray	vertical_ray_intersection(float ray_angle);
t_ray	horizontal_ray_intersection(float ray_angle);
int		check_wall(float x, float y);
void	draw_pixels(mlx_image_t **img, float h, float w, int color);
void	ru_first_check(t_ray *ray, float ray_angle);
#endif