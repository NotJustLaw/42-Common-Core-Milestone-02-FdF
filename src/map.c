/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:39:25 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/13 16:48:16 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	xy_alloc(char *filename, t_map_list *map)
{
	char	*line;
	int		fd;
	char	**tokens;
	
	fd = fd_in_handler(filename);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (ft_putstr_fd("Empty file\n", 2), -1);
	}
	tokens = ft_split(line, ' ');
	map->width = count_tokens(tokens);
	free_split(tokens);
	map->height = 0;
	while(line)
	{
		map->height += 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	map_grid_alloc(t_map_list *map)
{
	int	row;
	
	map->grid = (int **) malloc(sizeof(int *) * map->height);
	if (!map->grid)
		return (ft_putstr_fd("The map grid allocator suffered an error\n", 2), -1);
	row = 0;
	while (row < map->height)
	{
		map->grid[row] = (int *) malloc(sizeof(int) * map->width);
		if (!map->grid[row])
		{
			free_int_arr(map->grid, row);
			return (ft_putstr_fd("The map row allocator suffered an error\n", 2), -1);
		}
		row++;
	}
	return (0);
}

int	grid_map_filler(char *filename, t_map_list *map)
{
	int		fd;

	fd = fd_in_handler(filename);
	if (fd < 0)
		return (-1);
	if (filler(fd, map) < 0)
		return (ft_putstr_fd("Couldn't fill the map\n", 2), close(fd), -1);
	close(fd);
	return (0);
}

