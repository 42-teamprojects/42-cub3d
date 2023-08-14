/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/14 19:47:39 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(float move_speed, double x_axis_angle, double y_axis_angle)
{
	t_cords	new_pos;
	t_cords	map_pos;
	t_cords	player_pos;

	new_pos.x = g_game->player.x + x_axis_angle * move_speed;
	new_pos.y = g_game->player.y + y_axis_angle * move_speed;
	map_pos.x = new_pos.x / TILE_SIZE;
	map_pos.y = new_pos.y / TILE_SIZE;
	player_pos.x = g_game->player.x / TILE_SIZE;
	player_pos.y = g_game->player.y / TILE_SIZE;
	if (g_game->map->map[(int)map_pos.y][(int)map_pos.x] != '1' \
		&& g_game->map->map[(int)map_pos.y][(int)player_pos.x] != '1' \
		&& g_game->map->map[(int)player_pos.y][(int)map_pos.x] != '1')
	{
		g_game->player.x = new_pos.x;
		g_game->player.y = new_pos.y;
	}
}

void	handle_movement(float move_speed)
{
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_W))
		move(move_speed, cos(g_game->player.angle), \
			sin(g_game->player.angle));
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_S))
		move(move_speed, -cos(g_game->player.angle), \
			-sin(g_game->player.angle));
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_A))
		move(move_speed, sin(g_game->player.angle), \
			-cos(g_game->player.angle));
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_D))
		move(move_speed, -sin(g_game->player.angle), \
			cos(g_game->player.angle));
}

void	handle_rotation(float rot_speed)
{
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_LEFT))
	{
		g_game->player.angle -= rot_speed;
		g_game->player.angle = normalize_angle(g_game->player.angle);
	}
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_RIGHT))
	{
		g_game->player.angle += rot_speed;
		g_game->player.angle = normalize_angle(g_game->player.angle);
	}
}

void	handle_input(void)
{
	float	move_speed;
	float	rot_speed;

	move_speed = 2;
	rot_speed = 0.05;
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g_game->mlx);
	handle_movement(move_speed);
	handle_rotation(rot_speed);
}

void	ft_hook(void *param)
{
	(void)param;
	handle_input();
	cast_ray();
	// draw_map();
}
