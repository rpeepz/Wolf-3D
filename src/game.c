/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:46:19 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/09 22:13:08 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		hook_close(t_game *game)
{
	hook_keydown(KEY_ESC, game);
	return (1);
}
int		press_start(int key, t_game *game)
{
	if (key == KEY_ENTER)
	{
		game->started = 1;
		start_game(game);
	}
	return (0);
}

void	splash(t_game *game)
{
	int tw;
	int th;

	tw = 0;
	th = 0;
	mlx_put_image_to_window(game->mlx, game->win,
	mlx_xpm_to_image(game->mlx, _splash_, &tw, &th),
	(WIDTH / 2 - (tw / 2)), (HEIGHT / 2 - (th / 2)));
	mlx_string_put(game->mlx, game->win, (WIDTH * 10 / 27), (HEIGHT * 10 / 25),
	(0xffefd5), "Press Enter to start");
	mlx_hook(game->win, 2, 0, press_start, game);
	mlx_loop(game->mlx);
}

void	render(t_game *game)
{
	t_point	pixel;
	t_point	test;
	int		color[3];
	int		hit;
	int		ceiling;
	int		floor;
	float	ray_angle;
	float	distance;

	game->player.fov = 3.14285f / 3.0f;
	pixel.x = -1;
	while (++pixel.x < WIDTH)
	{
		ray_angle = (game->player.angle - (game->player.fov / 2)) +
					(pixel.x / WIDTH) * game->player.fov;
		distance = 0;
		hit = 0;
		game->player.eye.x = sinf(ray_angle);
		game->player.eye.y = cosf(ray_angle);
		while (!hit && distance < game->map->width)
		{
			distance += 0.1f;
			test.x = (int)game->player.loc.x + game->player.eye.x * distance;
			test.y = (int)game->player.loc.y + game->player.eye.y * distance;
			if ((int)test.x < 0 || (int)test.x >= game->map->width ||
				(int)test.y < 0 || (int)test.y >= game->map->height)
			{
				hit = 1;
				distance = game->map->width;
			}
			else
			{
				// printf("[test x %zu] ", test.x);
				// printf("[test y %zu] ", test.y);
				// printf("cell [%d]\n", game->map->cell[test.y][test.x]);
				if (game->map->cell[test.y][test.x] == 1)
					hit = 1;
				else if (game->map->cell[test.y][test.x] == 2)
					hit = 2;
				else if (game->map->cell[test.y][test.x] == 3)
					hit = 3;
			}
		}
		ceiling = ((float)HEIGHT / 2) - HEIGHT / (float)distance;
		floor = HEIGHT - ceiling;
		if (distance <= game->map->width / 4.0f) {
			color[0] = 0xFFFFFF;
			color[1] = 0xFF00FF;
			color[2] = 0x10FFFF;
		}
		else if (distance < game->map->width / 3.0f) {
			color[0] = 0xAAAAAA;
			color[1] = 0xAA00AA;
			color[2] = 0x10AAAA;
		}
		else if (distance < game->map->width / 2.0f) {
			color[0] = 0x555555;
			color[1] = 0x550055;
			color[2] = 0x105555;
		}
		else if (distance < game->map->width) {
			color[0] = 0x111111;
			color[1] = 0x110011;
			color[2] = 0x101111;
		}
		else {
			color[0] = 0x0;
			color[1] = 0x0;
			color[2] = 0x0;
		}
		
		pixel.y = -1;
		while (++pixel.y < HEIGHT)
		{
			if ((int)pixel.y < ceiling)
				*(int *)(game->image->pixels +
					(pixel.x + pixel.y * WIDTH) * game->image->bpp) = 0;
			else if ((int)pixel.y > ceiling && (int)pixel.y <= floor)
				*(int *)(game->image->pixels +
					(pixel.x + pixel.y * WIDTH) * game->image->bpp) = color[hit - 1];
			else
				*(int *)(game->image->pixels +
					(pixel.x + pixel.y * WIDTH) * game->image->bpp) = 0;
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->image->image, 0, 0);

}

void	start_game(t_game *game)
{
	if (!game->started)
		splash(game);
	game->player.loc.x = game->map->width / 2;
	game->player.loc.y = game->map->height / 2;
	game->player.angle = 0.0f;

	render(game);
	// enter_view(game);
	mlx_do_key_autorepeaton(game->mlx);
	mlx_hook(game->win, 2, 0, hook_keydown, game);
	// mlx_hook(game->win, 3, 0, hook_keyup, game);
	mlx_hook(game->win, 4, 0, hook_mousedown, game);
	mlx_hook(game->win, 6, 0, hook_mousemove, game);
	mlx_hook(game->win, 17, 0, hook_close, game);
	mlx_loop(game->mlx);
}
