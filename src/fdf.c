/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:39:58 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/16 14:23:24 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	init_fdf(char *file, t_map_list *map, t_proj *p, t_vars *vars);

int	main(int ac, char *av[])
{
	t_map_list	map;
	t_proj		p1;
	t_vars		vars;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./fdf <file.fdf>\n", 2), 1);
	if (init_fdf(av[1], &map, &p1, &vars) < 0)
		return (1);
	render(&p1, &map, &vars.img);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.ptr, 0, 0);
	mlx_key_hook(vars.win, handle_key, &vars);
	mlx_hook(vars.win, 17, 0, handle_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

static int	init_fdf(char *file, t_map_list *map, t_proj *p, t_vars *vars)
{
	if (xy_alloc(file, map) < 0
		|| map_grid_alloc(map) < 0
		|| grid_map_filler(file, map) < 0)
		return (-1);
	init_proj(p, map);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (ft_putstr_fd("Failed to init MLX\n", 2), -1);
	vars->win = mlx_new_window(vars->mlx,
			p->win_w, p->win_h, "skuhlcke FdF Project");
	if (!vars->win)
		return (ft_putstr_fd("Failed to open window\n", 2), -1);
	vars->img.ptr = mlx_new_image(vars->mlx, p->win_w, p->win_h);
	if (!vars->img.ptr)
		return (ft_putstr_fd("Image init failed\n", 2), -1);
	vars->img.dat = mlx_get_data_addr(vars->img.ptr,
			&vars->img.bpp,
			&vars->img.line_len,
			&vars->img.endian);
	if (!vars->img.dat)
		return (ft_putstr_fd("Image init failed\n", 2), -1);
	vars->map = map;
	return (0);
}

void	init_proj(t_proj *p, t_map_list *map)
{
	p->map_w = map->width;
	p->map_h = map->height;
	p->win_w = 1000;
	p->win_h = 800;
	p->zoom = 30.0f;
	p->cos30 = 0.8660254f;
	p->sin30 = 0.5f;
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
