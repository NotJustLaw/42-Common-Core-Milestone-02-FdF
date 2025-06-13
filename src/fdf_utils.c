/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:34:53 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/13 16:49:15 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = NULL;
}

void	free_int_arr(int **arr, int rows_allocated)
{
	while (rows_allocated-- > 0)
		free(arr[rows_allocated]);
	free(arr);
}

int	handle_key(int keycode, void *param)
{
	t_vars	*v;

	v = (t_vars *)param;
	if (keycode == 65307)
	{
		ft_putstr_fd("Please wait until the window is closed properly\n", 1);
		cleanup(v);
		exit(0);
	}
	return (0);
}

int	handle_close(void *param)
{
	t_vars	*v;

	v = (t_vars *)param;
	ft_putstr_fd("Please wait until the window is closed properly\n", 1);
	cleanup(v);
	exit(0);
	return (0);
}
