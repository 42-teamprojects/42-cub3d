/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/09 17:28:06 by htalhaou         ###   ########.fr       */
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
		horizental_ray_intersection(rayAngle);
		i++;
	}
}

float normalize_angle(float rayAngle)
{
	if (rayAngle < 0)
		rayAngle = (2 * M_PI) + rayAngle;
	else if (rayAngle > 2 * M_PI)
		rayAngle = rayAngle - (2 * M_PI);
	return (rayAngle);
}

int check_wall(float x, float y)
{
	int x1;
	int y1;
	int lenx;
	
	x1 = x / TILE_SIZE;
	y1 = y / TILE_SIZE;
	lenx = ft_strlen(g_game->map->map[y1]);
	if(x1 < 0 || x1 > lenx || y1 < 0 || y1 > g_game->map->height)
		return (1);
	if (g_game->map->map[y1][x1] == '1')
		return (1);
	return (0);
}

t_cords horizental_ray_intersection(float rayAngle)
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
	float  foundhorzwallhit = 0;
	float horizwallhitx = 0;
	float horizwallhity = 0;
	Ay = (int)(g_game->player.y / TILE_SIZE) * TILE_SIZE;
	if (rayfacingdown)
		Ay += TILE_SIZE;
	Ax = g_game->player.x + (Ay - g_game->player.y) / tan(rayAngle);
	ystep = TILE_SIZE;
	if (rayfacingup)
		ystep *= -1;
	xstep = TILE_SIZE / tan(rayAngle);
	if (rayfacingleft && xstep > 0)
		xstep *= -1;
	if (rayfacingright && xstep < 0)
		xstep *= -1;
	float nexthorzX = Ax;
	float nexthorzY = Ay;
	if (rayfacingup)
		nexthorzY--;
	while (nexthorzX >= 0 && nexthorzX <= g_game->img_map->width  && nexthorzY >= 0 && nexthorzY <= g_game->img_map->height )
	{
		if (check_wall(nexthorzX, nexthorzY))
		{
			foundhorzwallhit = 1;
			horizwallhitx = nexthorzX;
			horizwallhity = nexthorzY;
			break;
		}
		else
		{
			nexthorzX += xstep;
			nexthorzY += ystep;
		}
	}
	float  foundvertiwallhit = 0;
	float verwallhitx = 0;
	float verwallhity = 0;
	float wasHitVertical = 0;
	Ax = (int)(g_game->player.x / TILE_SIZE) * TILE_SIZE;
	if (rayfacingright)
		Ax += TILE_SIZE;
	Ay = g_game->player.y + (Ax - g_game->player.x) * tan(rayAngle);
	xstep = TILE_SIZE; 
	if (rayfacingleft)
		xstep *= -1;
	ystep = TILE_SIZE * tan(rayAngle);
	if (rayfacingup && ystep > 0)
		ystep *= -1;
	if (rayfacingdown && ystep < 0)
		ystep *= -1;
	float nextvertzX = Ax;
	float nextvertzY = Ay;
	if (rayfacingleft)
		nextvertzX--;
	while (nextvertzX >= 0 && nextvertzX <= g_game->img_map->width && nextvertzY >= 0 && nextvertzY <= g_game->img_map->height)
	{
		if (check_wall(nextvertzX, nextvertzY))
		{
			foundvertiwallhit = 1;
			verwallhitx = nextvertzX;
			verwallhity = nextvertzY;
			break;
		}
		else
		{
			nextvertzX += xstep;
			nextvertzY += ystep;
		}
	}
	float horzhitdistance;
	if (foundhorzwallhit)
		horzhitdistance = distance_between_points(g_game->player.x, g_game->player.y, horizwallhitx, horizwallhity);
	else
		horzhitdistance = 2000;
	
	float vertidistance;
	float wallhitx;
	float wallhity;
	float distance;
	if (foundvertiwallhit)
		vertidistance = distance_between_points(g_game->player.x, g_game->player.y, verwallhitx, verwallhity);
	else
		vertidistance = 2000;
	if (horzhitdistance < vertidistance)
		wallhitx = horizwallhitx;
	else
		wallhitx = verwallhitx;
	if (horzhitdistance < vertidistance)
		wallhity = horizwallhity;
	else
		wallhity = verwallhity;

	if (horzhitdistance < vertidistance)
		distance = horzhitdistance;
	else
		distance = vertidistance;
	if (vertidistance < horzhitdistance)
		wasHitVertical = 1;
	else
		wasHitVertical = 0;
	DDA(&g_game->img_map, g_game->player.x, g_game->player.y, wallhitx , wallhity);
	t_cords wallhit_cords;
	wallhit_cords.x = verwallhitx;
	wallhit_cords.y = verwallhity;
	return (wallhit_cords);
}

int distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}