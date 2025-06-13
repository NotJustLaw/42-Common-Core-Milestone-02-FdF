/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_compat.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:04:07 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/13 16:24:27 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_COMPAT_H
# define FDF_COMPAT_H

# ifdef __linux__
	#  include <mlx.h>

static inline void	destroy_display(void *mlx)
{
	mlx_destroy_display(mlx);
}

# else

static inline void	destroy_display(void *mlx)
{
	(void)mlx;
}

# endif

#endif
