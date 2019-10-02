/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/01 06:37:00 by rpapagna         ###   ########.fr       */
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
	if (key == KEY_PLUS && (DEBUG ? ft_out(key) : 1))
		game->cam->offsetz += 2;
	else if (key == KEY_MINUS && (DEBUG ? ft_out(key) : 1))
		game->cam->offsetz -= 2;
	else if (key == KEY_SPACE && (DEBUG ? ft_out(key) : 1))
	{
		game->cam->offsetz += 5;
		render(game);
		game->cam->offsetz -= 5;
	}
	else if ((key == KEY_UP || key == KEY_DOWN) && (DEBUG ? ft_out(key) : 1))
		game->cam->offsety -= (key == KEY_UP) ? 0.35 : -0.35;
	else if ((key == KEY_RIGHT || key == KEY_LEFT) && (DEBUG ? ft_out(key) : 1))
		game->cam->offsetx -= (key == KEY_LEFT) ? 0.35 : -0.35;
}

int				hook_keydown(int key, t_game *game)
{
	if (VALID_IN_X(key) || VALID_IN_Y(key) || VALID_IN_Z(key))
		in_key(game, key);
	else if (STATIC_ZOOM(key))
		hook_mousedown(key, 0, 0, game);
	else if (key == KEY_P && (DEBUG ? printf("Key: 'P' Pause: %s\n",
		game->in->mouse->lock ? "Off" : "On") : 1))
		game->in->mouse->lock = (game->in->mouse->lock) ? 0 : 1;
	else if (key == KEY_R && (DEBUG ? ft_out(key) : 1))
	{
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
	if (VALID_IN_X(key) || VALID_IN_Y(key) || VALID_IN_Z(key))
		render(game);
	return (0);
}

int				hook_close(t_game *game)
{
	hook_keydown(KEY_ESC, game);
	return (1);
}
