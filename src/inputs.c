/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/10 23:39:50 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int				hook_mousedown(int in, int x, int y, t_game *game)
{
	double		zoom;

	(void)y;
	(void)x;
	if (in == SCROLL_UP || in == SCROLL_DOWN || STATIC_ZOOM(in))
	{
		zoom = (game->cam.zoom / 100 + 1);
		if ((in == SCROLL_DOWN || in == PG_DOWN) && (zoom > game->cam.zoom))
			(DEBUG ? printf("Minimum Zoom reached\n") : 0);
		else
		{
			if ((in == SCROLL_UP || in == PG_UP) && (DEBUG ? ft_out(in) : 1))
				game->cam.zoom += zoom;
			else if ((in == SCROLL_DOWN || in == PG_DOWN) &&
				(DEBUG ? ft_out(in) : 1))
				game->cam.zoom -= zoom;
			if (DEBUG ? printf("%f\n", game->cam.zoom) : 1 && !STATIC_ZOOM(in))
			{
				;
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

static int		check_clip(t_game game, int key)
{
	game.player.loc.x += sinf(game.player.angle) * ((key == KEY_UP) ?
	0.5f : -0.5f);
	game.player.loc.y += cosf(game.player.angle) * ((key == KEY_UP) ?
	0.5f : -0.5f);
	if ((int)game.player.loc.y < 0 || (int)game.player.loc.y > game.map->height
	|| (int)game.player.loc.x < 0|| (int)game.player.loc.x > game.map->width ||
	!(game.map->cell[(int)game.player.loc.y][(int)game.player.loc.x]))
		return (0);
	return (1);
}

static void		in_key(t_game *game, int key)
{
	if ((key == KEY_PLUS || key == KEY_MINUS) && (DEBUG ? ft_out(key) : 1))
	{
		if ((key == KEY_PLUS && game->cam.offsetz < (HEIGHT - 2)) ||
		(key == KEY_MINUS && game->cam.offsetz > (2 - HEIGHT)))
			game->cam.offsetz += (key == KEY_PLUS) ? 2 : -2;
		(DEBUG ? printf("%f\n", game->cam.offsetz) : 0);
	}
	else if ((VALID_IN_Y(key)) && (DEBUG ? ft_out(key) : 1))
	{
		if (check_clip(*game, key))
			return ;
		game->player.loc.x += sinf(game->player.angle) * ((key == KEY_UP) ?
		0.5f : -0.5f);
		game->player.loc.y += cosf(game->player.angle) * ((key == KEY_UP) ?
		0.5f : -0.5f);
	}
	else if ((VALID_IN_X(key)) && (DEBUG ? ft_out(key) : 1))
		game->player.angle -= (key == KEY_LEFT) ? 0.03f : -0.03f;
	(DEBUG && VALID_IN_X(key)) ? printf("%f\n", game->player.angle) : 0;
	(DEBUG && VALID_IN_Y(key)) ? printf("%f, %f\n",
		game->player.loc.x, game->player.loc.y) : 0;
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
		DEBUG ? printf("z %f\n", game->cam.offsetz) : 0;
		game->cam.offsetz = 0.0f;
		game->cam.zoom = 1.0f;
		game->player.fov = 3.14285f / 4.0f;
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
