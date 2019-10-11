/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:02:28 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/10 16:22:38 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/wolf3d.h"

int			del_array(char **arr, int len)
{
	int		i;

	i = 0;
	if (!len || !arr)
		return (-42);
	while (i < len)
		ft_strdel(&(arr[i++]));
	ft_memdel((void **)&arr);
	return (-42);
}

void		del_map(t_map *map)
{
	int i;

	i = 0;
	while (map->cell && i < map->height)
	{
		if (map->cell[i])
			ft_memdel((void **)&map->cell[i]);
		i++;
	}
	if (map->cell)
		ft_memdel((void **)&map->cell);
}

t_image		*del_image(t_game *game, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(game->mlx, img->image);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

t_game		*del_game(t_game **agame, int i)
{
	t_game	*game;

	game = *agame;
	if (game->in != NULL)
	{
		IF_THEN(game->in->mouse != NULL, ft_memdel((void **)&game->in->mouse));
		IF_THEN(game->in->key != NULL, ft_memdel((void **)&game->in->key));
	}
	IF_THEN(game->in != NULL, ft_memdel((void **)&game->in));
	IF_THEN(game->image != NULL, del_image(game, game->image));
	if (game->scene != NULL)
	{
		while (i < LAYERS)
			IF_THEN(game->scene[i], ft_memdel((void **)&game->scene[i++]));
	}
	IF_THEN(game->scene != NULL, ft_memdel((void **)game->scene));
	IF_THEN(game->win != NULL, mlx_destroy_window(game->mlx, game->win));
	IF_THEN(game->mlx != NULL, ft_memdel((void **)&game->mlx));
	IF_THEN(game->map != NULL, del_map(game->map));
	ft_memdel((void **)&game);
	return (NULL);
}
