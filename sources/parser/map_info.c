/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:27:46 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/03 17:28:31 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_info(char *line, t_info *info)
{
	char	**tmp;

	tmp = ft_split(line, " ");
	if (ft_arrlen(tmp) != 2)
		return (free_arr(tmp), 0);
	if (!info->no && !ft_strcmp(tmp[0], "NO"))
		info->no = ft_strdup(tmp[1]);
	else if (!info->so && !ft_strcmp(tmp[0], "SO"))
		info->so = ft_strdup(tmp[1]);
	else if (!info->we && !ft_strcmp(tmp[0], "WE"))
		info->we = ft_strdup(tmp[1]);
	else if (!info->ea && !ft_strcmp(tmp[0], "EA"))
		info->ea = ft_strdup(tmp[1]);
	else if (!info->_f && !ft_strcmp(tmp[0], "F"))
		info->_f = ft_strdup(tmp[1]);
	else if (!info->_c && !ft_strcmp(tmp[0], "C"))
		info->_c = ft_strdup(tmp[1]);
	else
		return (free_arr(tmp), 0);
	free_arr(tmp);
	return (1);
}

t_info	*check_infos(char **map)
{
	t_info	*info;
	int		i;

	info = (t_info *) ft_calloc(1, sizeof(t_info));
	if (!info)
		return (NULL);
	i = -1;
	while (map[++i] && !is_all_wall(map[i]))
	{
		if (!find_info(map[i], info))
			return (throw_err(ERR_INFO), free(info), NULL);
	}
	if (!found_info(info))
		return (free(info), NULL);
	info->last = i;
	return (info);
}

int	valid_rgb(char *str, int rgb[3])
{
	char	**tmp;
	int		i;

	tmp = ft_split(str, ",");
	if (ft_arrlen(tmp) != 3)
		return (free_arr(tmp), 0);
	i = -1;
	while (tmp[++i])
	{
		if (!ft_isnum(tmp[i]))
			return (free_arr(tmp), 0);
		if (ft_atoi(tmp[i]) < 0 || ft_atoi(tmp[i]) > 255)
			return (free_arr(tmp), 0);
		rgb[i] = ft_atoi(tmp[i]);
	}
	free_arr(tmp);
	return (1);
}

int	valid_info(t_info **info)
{
	if (!valid_rgb((*info)->_f, (*info)->f) \
		|| !valid_rgb((*info)->_c, (*info)->c))
		return (throw_err(ERR_RGB), 0);
	return (1);
}
