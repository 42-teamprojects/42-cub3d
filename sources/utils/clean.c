/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:06:12 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/21 11:29:14 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_info(t_info *info)
{
	if (info)
	{
		free(info->no);
		free(info->so);
		free(info->we);
		free(info->ea);
		free(info->_f);
		free(info->_c);
		free(info);
	}
}

void	free_map(t_map *map)
{
	int	i;

	if (map)
	{
		free_info(map->info);
		if (map->map)
		{
			i = 0;
			while (i < map->height)
				free(map->map[i++]);
			free(map->map);
		}
		free(map);
	}
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game->map);
	if (game->no)
		mlx_delete_texture(game->no);
	if (game->so)
		mlx_delete_texture(game->so);
	if (game->we)
		mlx_delete_texture(game->we);
	if (game->ea)
		mlx_delete_texture(game->ea);
	if (game->no_pxls)
		free(game->no_pxls);
	if (game->so_pxls)
		free(game->so_pxls);
	if (game->we_pxls)
		free(game->we_pxls);
	if (game->ea_pxls)
		free(game->ea_pxls);
}
