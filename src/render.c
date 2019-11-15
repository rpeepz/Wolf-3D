/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:11:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/15 15:44:23 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
**	assign values to the colors array by [r, g, b] (with shading by distance)
*/

void	color_get(int *color, float distance, float depth)
{
	int		mod;
	float	dist;

	dist = distance / depth;
	mod = dist * 255;
	if (mod >= 250 && DEBUG)
		printf("too dark here\n");
	color[0] = (255 - mod) << 16;
	color[0] += (255 - mod) << 8;
	color[0] += (255 - mod);
	color[1] = (255 - mod) << 16;
	color[1] += (255 - mod);
	color[2] = (255 - mod) << 8;
	color[2] += (255 - mod);
	color[3] = (255 - mod) << 16;
	color[3] += (255 - mod) << 8;
	color[4] = (255 - mod) << 16;
	color[5] = (255 - mod) << 8;
	color[6] = (255 - mod);
}

/*
**	replace current image with a set layer
*/

void	set_layer(t_game *game, int l)
{
	ft_memmove(game->image->pixels, game->scene[l],
		sizeof(game->image->pixels));
}

/*
**	get floor, ceiling, and wall pixel colors in current collumn
*/

void	get_hit(t_render *v, t_game *game)
{
	t_point		cast;

	v->distance = 0;
	v->hit = 0;
	while (!v->hit && v->distance < game->player.depth)
	{
		v->distance += 0.008f;
		cast.x = game->player.loc.x + game->player.eye.x * v->distance;
		cast.y = game->player.loc.y + game->player.eye.y * v->distance;
		if ((int)cast.x < 0 || (int)cast.x >= game->map->width ||
			(int)cast.y < 0 || (int)cast.y >= game->map->height)
		{
			v->hit = 1;
			v->distance = game->player.depth;
		}
		else
			v->hit = game->map->cell[cast.y][cast.x];
	}
	v->ceiling = ((float)HEIGHT / 2) - HEIGHT / (float)v->distance;
	v->floor = HEIGHT - v->ceiling;
}

void	draw_(t_game *game, t_render v, t_point pixel, int *color)
{
	if ((int)pixel.y <= v.ceiling)
		*(int *)(game->image->pixels +
		(pixel.x + pixel.y * WIDTH) * game->image->bpp) = 0x2A2A2A;
	else if ((int)pixel.y > v.ceiling && (int)pixel.y <= v.floor)
		*(int *)(game->image->pixels +
		(pixel.x + pixel.y * WIDTH) * game->image->bpp) =
			color[v.hit ? v.hit - 1 : 0];
	else
		*(int *)(game->image->pixels +
		(pixel.x + pixel.y * WIDTH) * game->image->bpp) = 0x06A6A6A;
}

/*
**	calculate from the current player location, the angle from which the rays are sent
**	and draw column by column the values retrieved from get_hit
*/

void	render(t_game *game)
{
	t_point		pixel;
	t_render	v;
	int			color[7];

	set_layer(game, 0);
	pixel.x = -1;
	while (++pixel.x < WIDTH)
	{
		v.ray_angle = (game->player.angle - (game->player.fov / 2.0)) +
					((float)pixel.x / (float)WIDTH) * game->player.fov;
		game->player.eye.x = sinf(v.ray_angle);
		game->player.eye.y = cosf(v.ray_angle);
		get_hit(&v, game);
		color_get(color, v.distance, game->player.depth);
		pixel.y = -1;
		while (++pixel.y < HEIGHT)
			draw_(game, v, pixel, color);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->image->image, 0, 0);
}
