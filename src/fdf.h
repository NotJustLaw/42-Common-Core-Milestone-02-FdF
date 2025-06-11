/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:33:06 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/11 15:00:37 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../gnl/get_next_line_bonus.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_map_list
{
	int	height;
	int	width;
	int	**grid;
}		t_map_list;

typedef struct s_point2
{
	int	x;
	int	y;
}		t_point2;

typedef struct s_point3
{
	int	x;
	int	y;
	int	z;
}		t_point3;

typedef struct s_proj
{
	int 	map_w;
	int		map_h;
	int 	win_w;
	int		win_h;
	float	zoom;
	float	cos30;
	float	sin30;
}		t_proj;

typedef struct s_img
{
	void	*ptr;
	char	*dat;
	int		bpp;
	int		line_len;
	int		endian;
}		t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map_list	*map;
}		t_vars;

//Map-Wise
int		xy_alloc(char *filename, t_map_list *map);
int		map_grid_alloc(t_map_list *map);
int		grid_map_filler(char *filename, t_map_list *map);

//Map Utils
int		count_tokens(char **tokens);
void	free_partial_grid(t_map_list *map, int rows_filled);
int		filler(int fd, t_map_list *map);

//Render
void	render(const t_proj *P, const t_map_list *map, t_img *img);

//Render Utils
void 	draw_row(const t_proj *P, const t_map_list *map, t_img *img, int r);
t_point2	project_iso(const t_proj *P, t_point3 in);
void	draw_line(t_point2 p0, t_point2 p1, t_img *img, const t_proj *P);
int in_bounds(const t_proj *P, t_point2 p);

//FD's Utils
int		fd_in_handler(char	*filename);

//Utils
void	free_split(char **arr);
void	free_int_arr(int **arr, int rows_allocated);
int		handle_key(int keycode, void *param);
int		handle_close(void *param);

//Project handler
void	init_proj(t_proj *P, t_map_list *map);
t_vars	copy_vars(void *win, void *mlx, t_img img, t_map_list *map);

#endif