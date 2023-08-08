/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/08 13:31:58 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cast_ray()
{
	float FOV = 60 * (M_PI / 180);
	int num_rays = g_game->img_map->width * TILE_SIZE;
	float rayAngle = g_game->player.angle - (FOV / 2);
	int i = 0;

	while (i < num_rays)
	{
		rayAngle += FOV / (float)num_rays;
		draw_angle_dda(&g_game->img_map, rayAngle);
		i++;
	}
}

// int normalize_angle()
// {
// 	g_game->player.angle = g_game->player.angle / (2 * M_PI);
// 	if (g_game->player.angle < 0)
// 		g_game->player.angle = (2 * M_PI) + g_game->player.angle;
// 	return ((float)g_game->player.angle);
// }

void horizental_ray_intersection(float rayAngle)
{
	float Ax;
	float Ay;
	float xstep;
	float ystep;
	rayAngle = normalize_angle(rayAngle);
	float rayfacingdown = rayAngle > 0 && rayAngle < M_PI;
	float rayfacingup = !rayfacingdown;
	float rayfacingright = rayAngle < (M_PI / 2 ) || rayAngle > (3 * M_PI) / 2;
	float rayfacingleft = !rayfacingright;

	Ay = (int)(g_game->player.y / TILE_SIZE) * TILE_SIZE;
	if (rayfacingdown)
		Ay += TILE_SIZE;
	Ax = g_game->player.x + (Ay - g_game->player.y) / tan(rayAngle);
	ystep = TILE_SIZE;
	if (rayfacingup)
		ystep *= -1;
	xstep = ystep / tan(rayAngle);
	if (rayfacingleft && xstep > 0)
		xstep *= -1;
	if (rayfacingright && xstep < 0)
		xstep *= -1;
}