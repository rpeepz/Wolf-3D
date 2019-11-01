/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 04:17:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/14 19:38:24 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/wolf3d.h"

static t_image	*new_image(t_game *game)
{
	t_image		*img;

	if (!(img = ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(img->image = mlx_new_image(game->mlx, WIDTH, HEIGHT)))
		return (del_image(game, img));
	img->pixels = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
			&img->endian);
	img->bpp /= 8;
	return (img);
}

t_game			*init(char *title, t_map *map)
{
	t_game	*game;
	int		i;

	if (!(game = ft_memalloc(sizeof(t_game))))
		return (NULL);
	game->map = map;
	if (!(game->mlx = mlx_init()) ||
		!(game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, title)) ||
		!(game->scene = ft_memalloc(sizeof(char *) * LAYERS)) ||
		!(game->image = new_image(game)) ||
		!(game->in = ft_memalloc(sizeof(t_input))) ||
		!(game->in->key = ft_memalloc(sizeof(t_keys))) ||
		!(game->in->mouse = ft_memalloc(sizeof(t_mouse))))
		return (del_game(&game, 0));
	i = 0;
	while (i < LAYERS)
		game->scene[i++] = ft_memalloc(sizeof(game->image->pixels));
	game->player.loc.x = (float)game->map->width / 2;
	game->player.loc.y = (float)game->map->height / 2;
	game->player.angle = 0.0f;
	game->player.fov = 3.14159f / 4.0f;
	game->player.depth = map->height > map->width ? map->height : map->width;
	game->cam.offsetz = 0.0f;
	game->cam.zoom = 1.0f;
	return (game);
}
