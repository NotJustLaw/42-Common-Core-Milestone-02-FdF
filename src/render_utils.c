/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:28:07 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/11 15:21:39 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_row(const t_proj *P, const t_map_list *map, t_img *img, int r)
{
	int			c;
	t_point2	p0;
	t_point2	p1;

	c = 0;
	while (c < map->width)
	{
		p0 = project_iso(P, (t_point3){c, r, map->grid[r][c]});
		if (p0.x < 0 || p0.y < 0 || p0.x >= P->win_w || p0.y >= P->win_h)
		{
			printf("Out‐of‐bounds at row %d col %d → (%d,%d)\n",
				r, c, p0.x, p0.y);
			exit(1);
		}		
		if (c + 1 < map->width)
		{
			p1 = project_iso(P,
			(t_point3){c + 1, r, map->grid[r][c + 1]});
			if (p1.x < 0 || p1.y < 0 || p1.x >= P->win_w || p1.y >= P->win_h)
			{
				printf("Out-of-bounds neighbor at row %d col %d → (%d,%d)\n",
				r, c + 1, p1.x, p1.y);
				exit(1);
			}
			draw_line(p0, p1, img, P);
		}
		if (r + 1 < map->height)
		{
			p1 = project_iso(P,
			(t_point3){c, r + 1, map->grid[r + 1][c]});
			if (p1.x < 0 || p1.y < 0 || p1.x >= P->win_w || p1.y >= P->win_h)
			{
				printf("Out-of-bounds neighbor at row %d col %d → (%d,%d)\n",
				r, c + 1, p1.x, p1.y);
				exit(1);
			}
			draw_line(p0, p1, img, P);
		}
		c++;
	}
}

int in_bounds(const t_proj *P, t_point2 p)
{
	return (p.x >= 0 && p.y >= 0
		&& p.x <  P->win_w
		&& p.y <  P->win_h);
}
