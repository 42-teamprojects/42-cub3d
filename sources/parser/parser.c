/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/21 11:07:12 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*get_map(char *file)
{
	int		fd;
	char	*map_str;
	char	**map_arr;
	t_map	*map;

	map_arr = NULL;
	if (!check_file(file, &fd))
		return (0);
	map_str = read_map(fd);
	if (!map_str)
		return (0);
	map_arr = ft_split(map_str, "\n");
	free(map_str);
	map = check_map(map_arr);
	free_arr(map_arr);
	if (!map)
		exit(1);
	return (map);
}
