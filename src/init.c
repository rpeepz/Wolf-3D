/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 04:17:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/01 07:10:15 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

void			init_pix(t_pix *pix, t_game *game)
{
	pix->w = 5;
	pix->h = (pix->w * HEIGHT) / WIDTH;
	pix->xmin = -(pix->w / 2);
	pix->ymin = -(pix->h / 2);
	pix->xmax = pix->xmin + pix->w;
	pix->ymax = pix->ymin + pix->h;
	pix->xmin = pix->xmin - (WIDTH / 2) + game->cam->offsetx;
	pix->ymin = pix->ymin - (HEIGHT / 2) + game->cam->offsety;
	pix->xmax = pix->xmax - (WIDTH / 2) + game->cam->offsetx;
	pix->ymax = pix->ymax - (HEIGHT / 2) + game->cam->offsety;
}

t_image			*del_image(t_game *game, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(game->mlx, img->image);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

static t_image	*new_image(t_game *game)
{
	t_image		*img;

	if (!(img = ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(img->image = mlx_new_image(game->mlx, WIDTH, HEIGHT)))
		return (del_image(game, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
			&img->endian);
	img->bpp /= 8;
	return (img);
}

t_game			*del_game(t_game **agame, int i)
{
	t_game	*game;

	game = *agame;
	if (game->in != NULL)
	{
		IF_THEN(game->in->mouse != NULL, ft_memdel((void **)&game->in->mouse));
		IF_THEN(game->in->key != NULL, ft_memdel((void **)&game->in->key));
	}
	IF_THEN(game->in != NULL, ft_memdel((void **)&game->in));
	IF_THEN(game->cam != NULL, ft_memdel((void **)&game->cam));
	IF_THEN(game->image != NULL, del_image(game, game->image));
	if (game->scene != NULL)
	{
		while (i < LAYERS)
			IF_THEN(game->scene[i], ft_memdel((void **)&game->scene[i++]));
	}
	IF_THEN(game->scene != NULL, ft_memdel((void **)game->scene));
	IF_THEN(game->win != NULL, mlx_destroy_window(game->mlx, game->win));
	IF_THEN(game->mlx != NULL, ft_memdel((void **)&game->mlx));
	ft_memdel((void **)game);
	return (NULL);
}

t_game			*init(char *title, int type)
{
	t_game	*game;

	if (!(game = ft_memalloc(sizeof(t_game))))
		return (NULL);
	game->type = type;
	if (!(game->mlx = mlx_init()) ||
		!(game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, title)) ||
		!(game->scene = ft_memalloc(sizeof(char *) * LAYERS)) ||
		!(game->image = new_image(game)) ||
		!(game->cam = ft_memalloc(sizeof(t_camera))) ||
		!(game->in = ft_memalloc(sizeof(t_input))) ||
		!(game->in->key = ft_memalloc(sizeof(t_keys))) ||
		!(game->in->mouse = ft_memalloc(sizeof(t_mouse))))
		return (del_game(&game, 0));
	type = 0;
	while (type < LAYERS)
		game->scene[type++] = ft_memalloc(sizeof(game->image->ptr));
	game->cam->offsetx = WIDTH / 2;
	game->cam->offsety = HEIGHT / 2;;
	game->cam->zoom = 1.01;
	game->cam->scale = 1;
	return (game);
}
