/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:29:30 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/24 19:37:41 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	if (ac == 1 || ac > 2)
		return (throw_err(ERR_ARG), 1);
	if (init_game(av[1]))
		return (1);
	system("leaks cub3D -q");
	mlx_terminate(g_game->mlx);
	free_game(g_game);
	return (0);
}
