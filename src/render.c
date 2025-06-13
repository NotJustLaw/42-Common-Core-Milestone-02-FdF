/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:53:22 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/13 16:22:35 by skuhlcke         ###   ########.fr       */
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

static void	init_bres(t_bres *b, t_point2 p0, t_point2 p1)
{
	b->p0 = p0;
	b->p1 = p1;
	b->dx = abs(p1.x - p0.x);
	b->dy = abs(p1.y - p0.y);
	b->sx = (p0.x < p1.x) ? 1 : -1;
	b->sy = (p0.y < p1.y) ? 1 : -1;
	b->err = b->dx - b->dy;
}

static void	plot_bres_pixel(t_bres *b)
{
	size_t	offset;
	int		px_size;

	px_size = b->img->bpp / 8;
	offset = (size_t)b->p0.y * b->img->line_len
	       + (size_t)b->p0.x * px_size;
	*(unsigned int *)(b->img->dat + offset) = 0xFFFFFF;
}

void	draw_line(t_point2 p0, t_point2 p1, t_img *img, const t_proj *P)
{
	t_bres	b;
	int		e2;

	b.img = img;
	b.P = P;
	init_bres(&b, p0, p1);
	while (1)
	{
		if (in_bounds(P, b.p0))
			plot_bres_pixel(&b);
		if (b.p0.x == b.p1.x && b.p0.y == b.p1.y)
			break ;
		e2 = b.err * 2;
		if (e2 > -b.dy)
		{
			b.err -= b.dy;
			b.p0.x += b.sx;
		}
		if (e2 < b.dx)
		{
			b.err += b.dx;
			b.p0.y += b.sy;
		}
	}
}
