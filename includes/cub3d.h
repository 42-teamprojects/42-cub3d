/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:07:29 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/07 11:13:14 by htalhaou         ###   ########.fr       */
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

// Utils
void	throw_err(char *err);
void	free_arr(char **arr);
int		ft_arrlen(char **arr);
char	**ft_arrdup(char **arr);
// Clean up
void	free_game(t_game *game);
void	free_map(t_map *map);
void	free_info(t_info *info);

// raycasting

int		put_pixels(void);
void	DDA(mlx_image_t **img, float X0, float Y0, float X1, float Y1);
void	draw_angle_dda(mlx_image_t **img);
void	ft_hook(void* param);
void	draw_map();
#endif