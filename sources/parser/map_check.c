/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:58:12 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/03 21:24:49 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_cols(char **map)
{
	int	i;
	int	max;

	max = 0;
	i = 0;
	while (map[i])
	{
		if ((int) ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

int	is_valid_elements(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("01WNSE ", map[i][j]) == NULL)
				return (0);
			if (ft_strchr("WNSE", map[i][j]))
			{
				g_game->player.x = j;
				g_game->player.y = i;
				g_game->player.dir = map[i][j];
			}
			j++;
		}
		i++;
	}
	return (1);
}

// int containsOneWNSE(char** map, int rows, int cols) {
// 	int wnse_count = 0;
// 	int i = 0;

// 	while (i < rows) {
// 		int j = 0;
// 		while (j < cols) {
// 			char c = map[i][j];
// 			if (c == 'W' || c == 'N' || c == 'S' || c == 'E') {
// 				wnse_count++;
// 				if (wnse_count > 1) {
// 					return 0;
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}

// 	return wnse_count == 1;
// }

// Function to check if every '0' is surrounded by anything other than space
// int isValidZeroSurroundedByNonSpace(char** map, int rows, int cols) {
// 	int i = 1;
// 	while (i < rows - 1) {
// 		int j = 1;
// 		while (j < cols - 1) {
// 			if (map[i][j] == '0') {
// 				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
// 					map[i][j - 1] == ' ' || map[i][j + 1] == ' ') {
// 					return 0;
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}

// 	return 1;
// }

char	**valid_map(char **map, int *cols, int *rows)
{
	*cols = count_cols(map);
	*rows = ft_arrlen(map);
	return (is_valid_elements(map) ? map : NULL);
}

t_map	*check_map(char **map)
{
	t_map	*_map;

	_map = (t_map *) malloc(sizeof(t_map));
	if (!_map)
		return (NULL);
	_map->info = check_infos(map);
	if (!_map->info || (_map->info && !valid_info(&(_map->info))))
		return (NULL);
	_map->map = ft_arrdup(valid_map(map + _map->info->last, &_map->width, &_map->height));
	if (!_map->map)
		return (throw_err(ERR_ELEMS), NULL);
	return (_map);
}
