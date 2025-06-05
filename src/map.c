/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:39:25 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/05 18:02:37 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_reader(const char *filename, t_map_list map)
{
	char	*line;
	int		fd;
	int		height;
	char	**tokens;
	
	fd = fd_in_handler(filename);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (-1);
	}
	tokens = ft_split(line, ' ');
	map.width = count_tokens(tokens);
	map.height = 1;
	while((line = get_next_line(fd)))
	{
		map.height += 1;
		free(line);
	}
}

int	count_tokens(char **tokens)
{
	
}


