/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:53:22 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/11 15:21:14 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render(const t_proj *P, const t_map_list *map, t_img *img)
{
	int	r;

	r = 0;
	while (r < map->height)
	{
		draw_row(P, map, img, r);
		r++;
	}
}
/// @brief Takes a 3D grid coord and “tilts” it into 2D so it looks isometric
t_point2	project_iso(const t_proj *P, t_point3 in)
{
	float		x0;
	float		y0;
	float		z0;
	float		sx;
	float		sy;
	t_point2	out;

	x0 = in.x - (P->map_w - 1) / 2.0f;
	y0 = in.y - (P->map_h - 1) / 2.0f;
	z0 = in.z;
	sx = (x0 - y0) * P->cos30;
	sy = (x0 + y0) * P->sin30 - z0;
	sx = sx * P->zoom + P->win_w  / 2.0f;
	sy = sy * P->zoom + P->win_h  / 2.0f;
	out.x = (int)roundf(sx);
	out.y = (int)roundf(sy);
	return (out);
}

// static void bres_step_x(int *err, int dy, int *px, int sx)
// {
// 	if ((*err * 2) > -dy)
// 	{
// 		*err = *err - dy;
// 		*px += sx;
// 	}
// }

// static void bres_step_y(int *err, int dx, int *py, int sy)
// {
// 	if ((*err * 2) < dx)
// 	{
// 		*err = *err + dx;
// 		*py += sy;
// 	}
// }
/// @brief Bresenham’s line-drawing algorithm
void	draw_line(t_point2 p0, t_point2 p1, t_img *img, const t_proj *P)
{
	int 	dx;
	int 	dy;
	int 	sx;
	int 	sy;
	int 	err;
	size_t	offset;

	dx = abs(p1.x - p0.x);
	dy = abs(p1.y - p0.y);
	if (p0.x < p1.x)
		sx = 1;
	else
		sx = -1;
	if (p0.y < p1.y)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		if (in_bounds(P, p0))
		{
			int   px_size = img->bpp / 8;  
			offset = (size_t)p0.y * img->line_len
					+ (size_t)p0.x * px_size;
			*(unsigned int*)(img->dat + offset) = 0xFFFFFF;
		}
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		int e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			p0.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			p0.y += sy;
		}
	}
}
