/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:28:07 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/03 17:28:19 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_all_wall(char *line)
{
	int		i;
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] != '1' && tmp[i] != ' ')
			return (free(tmp), 0);
		i++;
	}
	free(tmp);
	return (1);
}

int	found_info(t_info *info)
{
	if (!info->no || !info->so || !info->we || !info->ea \
		|| !info->_f || !info->_c)
	{
		throw_err(ERR_ELEMS);
		return (0);
	}
	return (1);
}
