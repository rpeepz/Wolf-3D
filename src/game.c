/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:46:19 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/10 23:31:27 by rpapagna         ###   ########.fr       */
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

void	start_game(t_game *game)
{
	if (!game->started)
		splash(game);
	render(game);
	mlx_do_key_autorepeaton(game->mlx);
	mlx_hook(game->win, 2, 0, hook_keydown, game);
	mlx_hook(game->win, 4, 0, hook_mousedown, game);
	mlx_hook(game->win, 6, 0, hook_mousemove, game);
	mlx_hook(game->win, 17, 0, hook_close, game);
	mlx_loop(game->mlx);
}
