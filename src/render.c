/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:11:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/09 20:21:13 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	get_color(t_game *game, int *color, size_t z)
{
	if (z > (HEIGHT / 2) + game->cam->offsetz)
	{
		color[0] = (int)map_zero(game->in->mouse->x, HEIGHT, 0, 255);
		color[1] = 0;
		color[2] = (int)map_zero(game->cam->offsetz, 20, 0, 255);
	}
	else
	{
		color[0] = (int)map_zero(game->cam->offsetz, 20, 255, 0);
		color[1] = 0;
		color[2] = (int)map_zero(game->in->mouse->x, HEIGHT, 0, 255);
	}
}

// void	set_layer(t_game *game, int l)
// {
// 	ft_memmove(game->image->pixels, game->scene[l], sizeof(game->image->pixels));
// }

void	render1(t_game *game)
{
	t_point		pixel;
	size_t		z;
	int			color[3];

	z = 0;
	// set_layer(game, 0);
	if (SINGLE_CORE)
	{
		pixel.x = -1;
		while (++pixel.x < WIDTH)
		{
			pixel.y = -1;
			while (++pixel.y < HEIGHT)
			{
				get_color(game, color, pixel.y);
				*(int *)(game->image->pixels +
					(pixel.x + pixel.y * WIDTH) * game->image->bpp) =
					(color[0] << 16 | color[1] << 8 | color[2]);
			}
		}
	}
//	else
//	 	render_thread(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image->image, 0, 0);
	mlx_string_put(game->mlx, game->win, WIDTH / 2, HEIGHT / 2, (255 << 16 | 255 << 8 | 255), "HELLO");
}
