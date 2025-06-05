/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:33:06 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/05 18:02:59 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../gnl/get_next_line_bonus.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_map_list
{
	int	height;
	int	width;
	int	**grid;
}		t_map_list;

//Map-Wise
int	map_reader(const char *filename, t_map_list map);

//Map Utils
int	count_tokens(char **tokens);

//FD's Utils
int	fd_in_handler(char	*filename);

#endif