/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 03:38:46 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/01 04:01:04 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

int		main(int ac, char **av)
{
	t_game	*game;
	int		type;

	if (ac == 2)
		type = ft_atoi(av[1]);
	else if (av[1] && !ft_strcmp(av[1], "help"))
		return (ft_help());
	else
		return (ft_printf("%s\n", USAGE));
	if (!(game = init("Wolf 3D", type)))
		return (ft_out(-42));
	render(game);
	mlx_key_hook(game->win, hook_keydown, game);
	mlx_hook(game->win, 4, 0, hook_mousedown, game);
	mlx_hook(game->win, 6, 0, hook_mousemove, game);
	mlx_hook(game->win, 17, 0, hook_close, game);
	mlx_loop(game->mlx);
	return (0);
}
