/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/25 19:45:31 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** The move function updates the player's position based on the given move speed,
** x-axis angle, and y-axis angle. It checks if the new position is valid by
** checking the map at the new position and the player's current position.
** If the new position is valid, it updates the player's position.
*/
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
	if (g_game->map->map[(int)(map_pos.y - 0.1)][(int)(map_pos.x - 0.1)] != '1' \
		&& g_game->map->map[(int)map_pos.y][(int)player_pos.x] != '1' \
		&& g_game->map->map[(int)player_pos.y][(int)map_pos.x] != '1')
	{
		g_game->player.x = new_pos.x;
		g_game->player.y = new_pos.y;
	}
}

/*
** The handle_movement function handles the player's movement based on the keys
** pressed by the user. It calls the move function with the appropriate move speed
** and angle based on the key pressed.
*/
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

/*
** The handle_rotation function handles the player's rotation based on the keys
** pressed by the user. It updates the player's angle based on the rotation speed
** and the key pressed.
*/
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

/*
** The handle_input function handles the user's input by calling the handle_movement
** and handle_rotation functions with the appropriate move speed and rotation speed.
** It also checks if the user has pressed the escape key to close the window.
*/
void	handle_input(void)
{
	float	move_speed;
	float	rot_speed;

	move_speed = 4;
	rot_speed = 0.05;
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g_game->mlx);
	handle_movement(move_speed);
	handle_rotation(rot_speed);
}

/*
** The ft_hook function is the main function that is called by mlx_loop_hook.
** It calls the handle_input function to handle the user's input and then calls
** the cast_ray function to render the scene.
*/
void	ft_hook(void *param)
{
	(void)param;
	handle_input();
	cast_ray();
}
