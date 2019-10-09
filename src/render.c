/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:11:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/08 20:17:46 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	get_color(t_game *game, t_pix *pix, size_t z)
{
	if (z > (HEIGHT / 2) + game->cam->offsetz)
	{
		pix->color[0] = (int)map_zero(game->in->mouse->x, HEIGHT, 0, 255);
		pix->color[2] = (int)map_zero(game->cam->offsetz, 20, 0, 255);
	}
	else
	{
		pix->color[2] = (int)map_zero(game->in->mouse->x, HEIGHT, 0, 255);
		pix->color[0] = (int)map_zero(game->cam->offsetz, 20, 255, 0);
	}
}

void	set_layer(t_game *game, int l)
{
	ft_memmove(game->image->pixels, game->scene[l], sizeof(game->image->pixels));
}

void	render(t_game *game)
{
	t_point		pixel;
	t_pix		pix;
	size_t		z;

	z = 0;
	set_layer(game, 0);
	init_pix(&pix, game);
	if (SINGLE_CORE)
	{
		pixel.x = -1;
		while (++pixel.x < WIDTH)
		{
			pixel.y = -1;
			while (++pixel.y < HEIGHT)
			{
				get_color(game, &pix, pixel.y);
				*(int *)(game->image->pixels +
					(pixel.x + pixel.y * WIDTH) * game->image->bpp) =
					(pix.color[0] << 16 | pix.color[1] << 8 | pix.color[2]);
			}
		}
	}
//	else
//	 	render_thread(game, pix);
	mlx_put_image_to_window(game->mlx, game->win, game->image->image, 0, 0);
	mlx_string_put(game->mlx, game->win, WIDTH / 2, HEIGHT / 2, (255 << 16 | 255 << 8 | 255), "HELLO");
	// game->image->image = mlx_xpm_file_to_image(game->mlx, "../resources/splash.XPM", (int *)WIDTH, (int *)HEIGHT);
}
