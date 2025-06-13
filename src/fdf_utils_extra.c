/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:58:54 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/13 17:02:48 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_compat.h"

static void free_map(t_map_list *map)
{
	int	i;

	if (!map)
		return ;
	i = -1;
	while (++i < map->height)
		free(map->grid[i]);
	free(map->grid);
}

void	cleanup(t_vars *vars)
{
	get_next_line(-1);
	if (vars->img.ptr)
		mlx_destroy_image(vars->mlx, vars->img.ptr);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	destroy_display(vars->mlx);
	free(vars->mlx);
	free_map(vars->map);
}
