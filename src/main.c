/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 03:38:46 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/05 18:23:18 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		hook_close(t_game *game)
{
	hook_keydown(KEY_ESC, game);
	return (1);
}

int		main(int ac, char **av)
{
	t_game	*game;
	t_map	map;
	int		ret;

	if (ac == 2)
	{
		if (!ft_strcmp(av[1], "help"))
			return (ft_help());
		if ((ret = validate(av[1], &map)) <= 0)
			return (ft_out(ret));
	}
	else
		return (ft_printf("%s\n", USAGE));
	if (!(game = init("Wolf 3D", &map)))
		return (ft_out(-42));
	for (int i = 0; i < map.height; i++){
		for (int j = 0; j < map.width; j++){
			printf("%d ", map.cell[i][j]);
		}
		printf("\n");
	}
	render(game);
	mlx_do_key_autorepeaton(game->mlx);
	mlx_hook(game->win, 2, 0, hook_keydown, game);
	// mlx_hook(game->win, 3, 0, hook_keyup, game);
	mlx_hook(game->win, 4, 0, hook_mousedown, game);
	mlx_hook(game->win, 6, 0, hook_mousemove, game);
	mlx_hook(game->win, 17, 0, hook_close, game);
	mlx_loop(game->mlx);
	return (0);
}
