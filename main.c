/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:29:30 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/04 16:03:02 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(char *file)
{
	g_game = (t_game *) malloc(sizeof(t_game));
	g_game->map = parser(file);
	g_game->mlx = mlx_init(g_game->map->width * TILE_SIZE, \
		g_game->map->height * TILE_SIZE, "Cub3D", true);
	if (!g_game->mlx)
		return (1);
	// g_game->player.x *= TILE_SIZE;
	// g_game->player.y *= TILE_SIZE;
	draw_pixel();
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 1 || ac > 2)
		return (throw_err(ERR_ARG), 1);
	if (init_game(av[1]))
		return (1);
	mlx_loop(g_game->mlx);
	mlx_terminate(g_game->mlx);
	return (0);
}
