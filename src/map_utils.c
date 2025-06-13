/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:04:55 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/13 17:05:20 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_tokens(char **tokens)
{
	int	tokens_count;
	int	i;

	tokens_count = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != '\0')
			tokens_count++;
		i++;
	}
	return (tokens_count);
}

void	free_partial_grid(t_map_list *map, int rows_filled)
{
	while (rows_filled-- > 0)
		free(map->grid[rows_filled]);
	free(map->grid);
}

static int	fill_row(int fd, t_map_list *map, int row)
{
	char	*line;
	char	**tokens;
	int		token_count;
	int		col;

	line = get_next_line(fd);
	if (!line)
		return (free_partial_grid(map, row), get_next_line(-1), -1);
	tokens = ft_split(line, ' ');
	token_count = count_tokens(tokens);
	if (token_count != map->width)
	{
		fprintf(stderr, "Row %d has %d tokens but width is %d\n",
			row, token_count, map->width);
		free_split(tokens);
		free(line);
		free_int_arr(map->grid, map->height);
		return (get_next_line(-1), -1);
	}
	col = -1;
	while (++col < map->width)
		map->grid[row][col] = ft_atoi(tokens[col]);
	free_split(tokens);
	free(line);
	return (0);
}

int	filler(int fd, t_map_list *map)
{
	int	row;

	row = -1;
	while (++row < map->height)
		if (fill_row(fd, map, row) < 0)
			return (-1);
	return (0);
}
