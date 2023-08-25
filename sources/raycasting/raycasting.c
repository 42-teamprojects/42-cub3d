/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/25 19:10:15 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function calculates the distance and height of the wall that the ray
** intersects with. It does this by calculating the distance to the closest
** horizontal and vertical walls and then comparing them to determine which
** one is closer. It also applies a fish-eye fix to the distance calculation.
** Finally, it returns the ray that was used to calculate the wall distance and
** height.
*/
t_ray	get_ray(float ray_angle)
{
	t_ray	h_ray;
	t_ray	v_ray;
	float	fish_eye_fix;

	h_ray = horizontal_ray_intersection(ray_angle);
	v_ray = vertical_ray_intersection(ray_angle);
	if (h_ray.was_hit)
		h_ray.distance = distance_between_points(g_game->player.x, \
		g_game->player.y, h_ray.wall_hit_x, h_ray.wall_hit_y);
	else
		h_ray.distance = INT_MAX;
	if (v_ray.was_hit)
		v_ray.distance = distance_between_points(g_game->player.x, \
		g_game->player.y, v_ray.wall_hit_x, v_ray.wall_hit_y);
	else
		v_ray.distance = INT_MAX;
	fish_eye_fix = cos(ray_angle - g_game->player.angle);
	h_ray.wall_height = (HEIGHT / (h_ray.distance * fish_eye_fix / TILE_SIZE));
	v_ray.wall_height = (HEIGHT / (v_ray.distance * fish_eye_fix / TILE_SIZE));
	if (h_ray.distance < v_ray.distance)
		return ((h_ray.was_hit_vert = 0), h_ray);
	else
		return ((v_ray.was_hit_vert = 1), v_ray);
}

/*
** This function draws the floor and ceiling of the game window. It does this
** by iterating over each pixel in the window and setting its color to the
** appropriate color based on the map file's floor and ceiling colors.
*/
void	draw_fc(void)
{
	int i;
	int	j;
	
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
		{
			mlx_put_pixel(g_game->img_map, i, j, \
			get_rgba(g_game->map->info->c[0], g_game->map->info->c[1], \
			g_game->map->info->c[2], 1));
			j++;
		}
		j = HEIGHT / 2;
		while (j < HEIGHT)
		{
			mlx_put_pixel(g_game->img_map, i, j, \
			get_rgba(g_game->map->info->f[0], g_game->map->info->f[1], \
			g_game->map->info->f[2], 1));
			j++;
		}
		i++;
	}
}

/*
** This function casts rays from the player's position to the edges of the
** screen and draws the resulting walls to the game window. It does this by
** iterating over each ray and calling the get_ray function to calculate the
** distance and height of the wall that the ray intersects with. It then calls
** the draw_texture function to draw the wall to the game window.
*/
void	cast_ray(void)
{
	int		num_rays;
	float	ray_angle;
	t_ray	ray;
	t_cords	param;

	num_rays = WIDTH;
	ray_angle = g_game->player.angle - (g_game->player.fov / 2);
	draw_fc();
	param.x = 0;
	while (param.x < num_rays)
	{
		ray_angle += g_game->player.fov / num_rays;
		ray = get_ray(ray_angle);
		param.y = (HEIGHT / 2) - (ray.wall_height / 2);
		if (param.y < 0)
			param.y = 0;
		draw_texture(ray, param, ray.wall_height);
		param.x++;
	}
}

