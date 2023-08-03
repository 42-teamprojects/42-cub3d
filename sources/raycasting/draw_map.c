/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:18:23 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/03 18:39:04 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char g_map[10][10] = {
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', 'N', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

int sq_h = 64;
int sq_w = 64;

void draw_sqr(int tmp_x, int tmp_y, int i, int j)
{
    tmp_x = i * sq_w;
    while (tmp_x < i * sq_w + sq_w - 1)
    {
        tmp_y = j * sq_h;
        while (tmp_y < j * sq_h + sq_h - 1)
        {
            mlx_put_pixel(g_game->img, tmp_x, tmp_y , 0xffffffff);
            tmp_y++;
        }
        tmp_x++;
    }
}

void draw_player(int tmp_x, int tmp_y, int i, int j)
{
    tmp_x = i * sq_w;
    while (tmp_x < i * sq_w + sq_w - 60)
    {
        tmp_y = j * sq_h;
    while (tmp_y < j * sq_h + sq_h - 60)
    {
        mlx_put_pixel(g_game->img, tmp_x, tmp_y , 0xffffffff);
        tmp_y++;
    }
        tmp_x++;
    }
}

void put_elements()
{

	int j = 0;
	int i = -1;
    int tmp_x;
    int tmp_y;
	
    tmp_x = i * sq_w;
    tmp_y = j * sq_h;
    while (++i < 10)
    {
        j = 0;
        while (j < 10)
        {
            if(g_map[i][j] == '1')
                draw_sqr(tmp_x, tmp_y, i, j);
            else if (g_map[i][j] == 'N')
                draw_player(tmp_x, tmp_y, i, j);
            j++;
        }
    }
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		g_game->img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		g_game->img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		g_game->img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		g_game->img->instances[0].x += 5;
}


int draw_pixel(void)
{
    g_game->img = mlx_new_image(g_game->mlx, 1280, 720);
    if (!g_game->img)
        return (1);
    if (mlx_image_to_window(g_game->mlx, g_game->img, 0, 0) < 0)
        return (1);
    put_elements();
    mlx_loop_hook(g_game->mlx, ft_hook, g_game->mlx);
    mlx_loop(g_game->mlx);
    return (0);
}
