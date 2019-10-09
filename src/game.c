/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:46:19 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/08 17:05:30 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		hook_close(t_game *game)
{
	hook_keydown(KEY_ESC, game);
	return (1);
}

void	start_game(t_game *game)
{
	render(game);
	mlx_do_key_autorepeaton(game->mlx);
	mlx_hook(game->win, 2, 0, hook_keydown, game);
	// mlx_hook(game->win, 3, 0, hook_keyup, game);
	mlx_hook(game->win, 4, 0, hook_mousedown, game);
	mlx_hook(game->win, 6, 0, hook_mousemove, game);
	mlx_hook(game->win, 17, 0, hook_close, game);
	mlx_loop(game->mlx);
}
