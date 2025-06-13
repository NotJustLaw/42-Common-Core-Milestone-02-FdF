/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:28:07 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/13 17:25:51 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_right(const t_proj *P, t_img *img, t_point2 p0, t_point3 n)
{
	t_point2	p1;

	p1 = project_iso(P, n);
	draw_line(p0, p1, img, P);
}

static void	draw_down(const t_proj *P, t_img *img, t_point2 p0, t_point3 n)
{
	t_point2	p1;

	p1 = project_iso(P, n);
	draw_line(p0, p1, img, P);
}

void	draw_row(const t_proj *P, const t_map_list *map, t_img *img, int r)
{
	int			c;
	t_point2	p0;

	c = 0;
	while (c < map->width)
	{
		p0 = project_iso(P, (t_point3){c, r, map->grid[r][c]});
		if (c + 1 < map->width)
			draw_right(P, img, p0,
				(t_point3){c + 1, r, map->grid[r][c + 1]});
		if (r + 1 < map->height)
			draw_down(P, img, p0,
				(t_point3){c, r + 1, map->grid[r + 1][c]});
		c++;
	}
}


int in_bounds(const t_proj *P, t_point2 p)
{
	return (p.x >= 0 && p.y >= 0
		&& p.x <  P->win_w
		&& p.y <  P->win_h);
}
