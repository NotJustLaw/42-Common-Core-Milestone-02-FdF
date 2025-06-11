/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:39:58 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/11 15:20:46 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char *av[])
{
	t_map_list	map;
	t_proj		P;
	t_vars		vars;
	t_img		img;
	void		*mlx;
	void		*win;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./fdf <file.fdf>\n", 2), 1);
    if (xy_alloc(av[1], &map) < 0 || map_grid_alloc(&map) < 0
		|| grid_map_filler(av[1], &map) < 0)
			return (1);
	init_proj(&P, &map);
	mlx = mlx_init();
	if (!mlx)
		return(ft_putstr_fd("Failed to init MLX\n", 2), 1);
	win = mlx_new_window(mlx, P.win_w, P.win_h, "skuhlcke FdF Project");
	if (!win)
		return(ft_putstr_fd("Failed to open the window", 2), 1);
	img.ptr = mlx_new_image(mlx, P.win_w, P.win_h);
	img.dat = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
	vars = copy_vars(win, mlx, img, &map);
	if (!img.ptr || !img.dat)
		return (ft_putstr_fd("Image init failed\n", 2), 1);
	render(&P, &map, &img);
	mlx_put_image_to_window(mlx, win, img.ptr, 0, 0);
	mlx_key_hook(win, handle_key, &vars);
	mlx_hook(win, 17, 0, handle_close, &vars);
	mlx_loop(mlx);
	return (0);
}

void	init_proj(t_proj *P, t_map_list *map)
{
	P->map_w = map->width;
	P->map_h = map->height;
	P->win_w = 1000;
	P->win_h = 800;
	P->zoom = 20.0f;
	P->cos30 = 0.8660254f;
	P->sin30 = 0.5f;
}

t_vars	copy_vars(void *win, void *mlx, t_img img, t_map_list *map)
{
	t_vars	vars;

	vars.mlx = mlx;
	vars.win = win;
	vars.img = img;
	vars.map = map;
	return (vars);
}
