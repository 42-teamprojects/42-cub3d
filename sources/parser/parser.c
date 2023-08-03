/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/03 15:30:29 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*parser(char *file)
{
	t_map	*map;

	map = (t_map *) malloc(sizeof(t_map));
	printf("Parsing file %s\n", file);
	map = get_map(file);
	map->width = 640;
	map->height = 640;
	return (map);
}
