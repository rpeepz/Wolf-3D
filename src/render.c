/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:11:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/01 07:13:20 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	get_color(t_game *game, t_pix *pix, size_t n)
{
	(void)game;
	(void)n;
	pix->color[0] = (int)map_zero(game->in->mouse->y, HEIGHT, 0, 255);
	pix->color[1] = (int)map_zero(game->in->mouse->x, HEIGHT, 0, 255);
	pix->color[2] = (int)map_zero(game->cam->offsetz, 20, 0, 255);
}

void	get_game(t_game *game, t_pix *pix)
{
	if (game->type % 2)
	{
		pix->c[0] = pix->a;
		pix->c[1] = pix->b;
	}
	else
	{
		pix->c[0] = map_zero(game->in->mouse->y, HEIGHT, -1.5, 1.5);
		pix->c[1] = map_zero(game->in->mouse->x, WIDTH, -1.5, 1.5);
	}
}

size_t	define_pixel(t_point pixel, t_game *game, t_pix *pix)
{
	size_t		n;
	double		aa;
	double		bb;
	double		twoab;

	pix->a = (map_zero(pixel.x, WIDTH, pix->xmin, pix->xmax) /
		(game->cam->zoom));
	pix->b = (map_zero(pixel.y, HEIGHT, pix->ymin, pix->ymax) /
		(game->cam->zoom));
	get_game(game, pix);
	n = 0;
	while (n < 1)
	{
		aa = pix->a * pix->a;
		bb = pix->b * pix->b;
		twoab = 2.0 * pix->a * pix->b;
		pix->a = game->type > 2 ?
			abs_double(aa - bb + pix->c[0]) : aa - bb + pix->c[0];
		pix->b = game->type > 2 ?
			abs_double(twoab) + pix->c[1] : twoab + pix->c[1];
		if (pix->a * pix->a + pix->b * pix->b > 4)
			break ;
		n++;
	}
	return (n);
}

void	render(t_game *game)
{
	t_point		pixel;
	size_t		n;
	t_pix		pix;

	ft_memmove(game->image->ptr, game->scene[LAYERS - 1], sizeof(game->image->ptr));
	init_pix(&pix, game);
	if (SINGLE_CORE)
	{
		pixel.x = -1;
		while (++pixel.x < WIDTH)
		{
			pixel.y = -1;
			while (++pixel.y < HEIGHT)
			{
				n = define_pixel(pixel, game, &pix);
				get_color(game, &pix, n);
				*(int *)(game->image->ptr +
					(pixel.x + pixel.y * WIDTH) * game->image->bpp) =
					(pix.color[0] << 16 | pix.color[1] << 8 | pix.color[2]);
			}
		}
	}
//	else
//	 	render_thread(game, pix);
	mlx_put_image_to_window(game->mlx, game->win, game->image->image, 0, 0);
}
