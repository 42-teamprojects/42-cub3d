/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/03 17:15:01 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	throw_err(char *err)
{
	ft_printf_fd(2, BRED "Error\n"CX"%s\n", err);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**ft_arrdup(char **arr)
{
	char	**new;
	int		i;

	new = (char **) ft_calloc(ft_arrlen(arr) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	while (arr[++i])
		new[i] = ft_strdup(arr[i]);
	return (new);
}
