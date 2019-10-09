/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 03:38:46 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/08 20:10:17 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		main(int ac, char **av)
{
	t_game	*game;
	t_map	map;
	int		ret;

	ft_bzero(&map, sizeof(map));
	if (ac != 2)
		return (ft_printf("%s\n", USAGE));
	if (!ft_strcmp(av[1], "help"))
		return (ft_help());
	if ((ret = validate(av[1], &map)) <= 0)
		return (ft_out(ret));
	if (!(game = init("Wolf 3D", &map)))
		return (ft_out(-42));
	start_game(game);
	return (0);
}
