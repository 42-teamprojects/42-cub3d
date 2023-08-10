/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/10 19:58:57 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cast_ray()
{
	int num_rays = WIDTH * 2;
	float ray_angle = g_game->player.angle - (g_game->player.fov / 2);
	int i = 0;
	t_ray ray;
	while (i < num_rays)
	{
		ray_angle += g_game->player.fov / num_rays;
		ray = raycast(ray_angle);
		DDA(&g_game->img_map, g_game->player.x, g_game->player.y, ray.wall_hit_x, ray.wall_hit_y);
		i++;
	}
}

float normalize_angle(float ray_angle)
{
	if (ray_angle < 0)
		ray_angle = (2 * M_PI) + ray_angle;
	else if (ray_angle > 2 * M_PI)
		ray_angle = ray_angle - (2 * M_PI);
	return (ray_angle);
}

int check_wall(float x, float y)
{
	int x1;
	int y1;
	float lenx;

	
	x1 = x / TILE_SIZE;
	y1 = y / TILE_SIZE;
	lenx = ft_strlen(g_game->map->map[y1]);
	if(x1 < 0 || x1 >=lenx || y1 < 0 || y1 >= g_game->map->height)
		return (1);
	if (g_game->map->map[y1][x1] == '1')
		return (1);
	return (0);
}

int distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

t_ray	horizontal_ray_intersection(float ray_angle)
{
	t_cords A;
	t_cords step;
	t_cords next;
	t_cords check;
	t_ray ray;
	
	ray_angle = normalize_angle(ray_angle);
	ray.is_down = ray_angle > 0 && ray_angle < M_PI;
	ray.is_up = !ray.is_down;
	ray.is_right = ray_angle < (M_PI / 2 ) || ray_angle > (3 * M_PI) / 2;
	ray.is_left = !ray.is_right;

	ray.was_hit = 0;
	ray.wall_hit_x = 0;
	ray.wall_hit_y = 0;
	A.y = floor(g_game->player.y / TILE_SIZE) * TILE_SIZE;
	if (ray.is_down)
		A.y += TILE_SIZE;
	A.x = g_game->player.x + (A.y - g_game->player.y) / tan(ray_angle);
	step.y = TILE_SIZE;
	if (ray.is_up)
		step.y *= -1;
	step.x = TILE_SIZE / tan(ray_angle);
	if (ray.is_left && step.x > 0)
		step.x *= -1;
	if (ray.is_right && step.x < 0)
		step.x *= -1;
	
	next.x = A.x;
	next.y = A.y;
	while (next.x >= 0 && next.x <= g_game->img_map->width  && next.y >= 0 && next.y <= g_game->img_map->height )
	{
		if (ray.is_up)
			check.y = next.y - 1;
		else
			check.y = next.y;
		check.x = next.x;
		if (check_wall(check.x, check.y))
		{
			ray.was_hit = 1;
			ray.wall_hit_x = next.x;
			ray.wall_hit_y = next.y;
			break;
		}
		else
		{
			next.x += step.x;
			next.y += step.y;
		}
	}
	return (ray);
}

t_ray	vertical_ray_intersection(float ray_angle)
{
	t_cords A;
	t_cords step;
	t_cords next;
	t_cords check;
	t_ray ray;
	
	ray_angle = normalize_angle(ray_angle);
	ray.is_down = ray_angle > 0 && ray_angle < M_PI;
	ray.is_up = !ray.is_down;
	ray.is_right = ray_angle < (M_PI / 2 ) || ray_angle > (3 * M_PI) / 2;
	ray.is_left = !ray.is_right;

	ray.was_hit = 0;
	ray.wall_hit_x = 0;
	ray.wall_hit_y = 0;
	A.x = (int)(g_game->player.x / TILE_SIZE) * TILE_SIZE;
	if (ray.is_right)
		A.x += TILE_SIZE;
	A.y = g_game->player.y + (A.x - g_game->player.x) * tan(ray_angle);
	step.x = TILE_SIZE;
	if (ray.is_left)
		step.x *= -1;
	step.y = TILE_SIZE * tan(ray_angle);
	if (ray.is_up && step.y > 0)
		step.y *= -1;
	if (ray.is_down && step.y < 0)
		step.y *= -1;
	
	next.x = A.x;
	next.y = A.y;
	while (next.x >= 0 && next.x <= g_game->img_map->width  && next.y >= 0 && next.y <= g_game->img_map->height )
	{
		if (ray.is_left)
			check.x = next.x - 1;
		else
			check.x = next.x;
		check.y = next.y;
		if (check_wall(check.x, check.y))
		{
			ray.was_hit = 1;
			ray.wall_hit_x = next.x;
			ray.wall_hit_y = next.y;
			break;
		}
		else
		{
			next.x += step.x;
			next.y += step.y;
		}
	}
	return (ray);
}

t_ray	raycast(float ray_angle)
{
	t_ray	h_ray;
	t_ray	v_ray;

	h_ray = horizontal_ray_intersection(ray_angle);
	v_ray = vertical_ray_intersection(ray_angle);
	if (h_ray.was_hit)
		h_ray.distance = distance_between_points(g_game->player.x, g_game->player.y, h_ray.wall_hit_x, h_ray.wall_hit_y);
	else
		h_ray.distance = INT_MAX;
	if (v_ray.was_hit)
		v_ray.distance = distance_between_points(g_game->player.x, g_game->player.y, v_ray.wall_hit_x, v_ray.wall_hit_y);
	else
		v_ray.distance = INT_MAX;
	float fov_correction = cos(g_game->player.angle - g_game->player.fov / 2);
	if (h_ray.distance < v_ray.distance)
	{
		h_ray.wall_height = (HEIGHT) / ((h_ray.distance * fov_correction) / TILE_SIZE);
		return (h_ray);
	}
	else
	{
		v_ray.wall_height = (HEIGHT) / ((v_ray.distance * fov_correction) / TILE_SIZE);
		return (v_ray);
	}
}