/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/09 21:17:39 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int				hook_mousedown(int in, int x, int y, t_game *game)
{
	double		zoom;

	if (in == SCROLL_UP || in == SCROLL_DOWN || STATIC_ZOOM(in))
	{
		zoom = (game->cam->zoom / 100 + 1);
		if ((in == SCROLL_DOWN || in == PG_DOWN) && (zoom > game->cam->zoom))
			(DEBUG ? printf("Minimum Zoom reached\n") : 0);
		else
		{
			if ((in == SCROLL_UP || in == PG_UP) && (DEBUG ? ft_out(in) : 1))
				game->cam->zoom += zoom;
			else if ((in == SCROLL_DOWN || in == PG_DOWN) &&
				(DEBUG ? ft_out(in) : 1))
				game->cam->zoom -= zoom;
			if (DEBUG ? printf("%f\n", game->cam->zoom) : 1 && !STATIC_ZOOM(in))
			{
				game->cam->offsetx +=
				(0.0001 * game->cam->zoom) * (x - (WIDTH / 2));
				game->cam->offsety +=
				(0.0001 * game->cam->zoom) * (y - (HEIGHT / 2));
			}
			render(game);
		}
	}
	return (0);
}

int				hook_mousemove(int x, int y, t_game *game)
{
	if (!game->in->mouse->lock)
	{
		if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT)
		{
			game->in->mouse->lastx = game->in->mouse->x;
			game->in->mouse->lasty = game->in->mouse->y;
			game->in->mouse->x = x;
			game->in->mouse->y = y;
			render(game);
		}
	}
	else
	{
		;
	}
	return (0);
}

static void		in_key(t_game *game, int key)
{
	if ((key == KEY_PLUS || key == KEY_MINUS) && (DEBUG ? ft_out(key) : 1))
	{
		if ((key == KEY_PLUS && game->cam->offsetz < (HEIGHT - 2)) ||
		(key == KEY_MINUS && game->cam->offsetz > (2 - HEIGHT)))
			game->cam->offsetz += (key == KEY_PLUS) ? 2 : -2;
		(DEBUG ? printf("%f\n", game->cam->offsetz) : 0);
	}
	else if (key == KEY_SPACE && (DEBUG ? ft_out(key) : 1))
	{
		game->cam->offsetz += 10;
		render(game);
	}
	else if ((VALID_IN_Y(key)) && (DEBUG ? ft_out(key) : 1))
	{
		game->player.loc.x += (key == KEY_UP) ? sinf(game->player.angle) * 0.5f : sinf(game->player.angle) * -0.5f;
		game->player.loc.y += (key == KEY_UP) ? cosf(game->player.angle) * 0.5f : cosf(game->player.angle) * -0.5f;
		game->cam->offsety -= (key == KEY_UP) ? 0.35 : -0.35;
	}
	else if ((VALID_IN_X(key)) && (DEBUG ? ft_out(key) : 1))
	{
		game->player.angle -= (key == KEY_LEFT) ? 0.01f : -0.01f;
		game->cam->offsetx -= (key == KEY_LEFT) ? 0.35 : -0.35;
	}
	(DEBUG && VALID_IN_X(key)) ? printf("%f\n", game->cam->offsetx) : 0;
	(DEBUG && VALID_IN_Y(key)) ? printf("%f\n", game->cam->offsety) : 0;
}

int				hook_keydown(int key, t_game *game)
{
	if (VALID_IN_X(key) || VALID_IN_Y(key) || VALID_IN_Z(key))
		in_key(game, key);
	else if (STATIC_ZOOM(key))
		hook_mousedown(key, 0, 0, game);
	else if (key == KEY_P && printf("Key: 'P' Pause: %s\n",
		game->in->mouse->lock ? "Off" : "On"))
		game->in->mouse->lock = (game->in->mouse->lock) ? 0 : 1;
	else if (key == KEY_R && (DEBUG ? ft_out(key) : 1))
	{
		DEBUG ? printf("z %f\n", game->cam->offsetz) : 0;
		game->cam->offsetz = 0;
		game->cam->offsetx = WIDTH / 2;
		game->cam->offsety = HEIGHT / 2;
		game->cam->zoom = 1.01;
		game->cam->scale = 1;
	}
	else if (printf("---\n") && key == KEY_ESC && printf("Goodbye!\n"))
	{
		(DEBUG ? system("leaks wolf3d") : 1);
		exit((int)del_game(&game, 0));
	}
	if (VALID_IN_X(key) || VALID_IN_Y(key) || VALID_IN_Z(key) || key == KEY_R)
		render(game);
	return (0);
}
