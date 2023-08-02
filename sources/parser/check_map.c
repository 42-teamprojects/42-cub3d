/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:58:06 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/02 21:04:44 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*check_map(char **map)
{
	int		i;
	t_map	*_map;

	_map = (t_map *) malloc(sizeof(t_map));
	return (_map);
	i = 0;
	while (map[i])
	{
		if (ft_strnstr(map[i], "NO", 2) || ft_strnstr(map[i], "SO", 2) \
			|| ft_strnstr(map[i], "WE", 2) || ft_strnstr(map[i], "EA", 2) \
			|| ft_strnstr(map[i], "F", 1) || ft_strnstr(map[i], "C", 1))
			return (0);
	}
	return (_map);
}
