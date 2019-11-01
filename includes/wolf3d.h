/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 00:21:10 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/14 19:26:41 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx/includes/mlx.h"
# include "../resources/splash.xpm"
# include "keys.h"
# include <math.h>
# include <pthread.h>
# include <stdio.h>

# define USAGE "usage: ./wolf3d [ file.map ]"
# define WIDTH 1280
# define HEIGHT 720
# define VALID_IN_X(x) (x == KEY_RIGHT || x == KEY_LEFT)
# define VALID_IN_Y(x) (x == KEY_UP || x == KEY_DOWN)
# define VALID_IN_Z(x) (x == KEY_PLUS || x == KEY_MINUS || x == KEY_SPACE)
# define STATIC_ZOOM(x) (x == PG_UP || x == PG_DOWN)
# define LAYERS 5
# define PI 3.1415926535
# define SINGLE_CORE 1
# define THREAD_COUNT 8
# ifdef _DEBUG_RULE_
#  define DEBUG 1
# else
#  define DEBUG 0
# endif

/*
**	STRUCTS
*/

typedef struct			s_2dp
{
	double				x;
	double				y;
}						t_2dp;

typedef struct			s_map
{
	int					width;
	int					height;
	int					**cell;
}						t_map;

typedef struct			s_image
{
	void				*image;
	char				*pixels;
	int					bpp;
	int					stride;
	int					endian;
}						t_image;

typedef struct			s_camera
{
	double				offsetz;
	double				zoom;
}						t_camera;

typedef struct			s_input
{
	struct s_keys		*key;
	struct s_mouse		*mouse;
	char				key_down[4];
}						t_input;

typedef struct			s_player
{
	t_2dp				loc;
	t_2dp				eye;
	float				angle;
	float				fov;
	float				depth;
}						t_player;

typedef struct			s_render
{
	float				ray_angle;
	float				distance;
	int					hit;
	int					ceiling;
	int					floor;
}						t_render;

typedef struct			s_game
{
	char				started;
	t_player			player;
	t_camera			cam;
	void				*mlx;
	void				*win;
	char				**scene;
	t_map				*map;
	t_image				*image;
	t_input				*in;
}						t_game;

typedef struct			s_game_thread
{
	t_game				*game;
	int					i;
}						t_game_thread;

/*
**void					render_thread(t_game *game);
*/

void					render(t_game *game);
void					start_game(t_game *game);

int						del_array(char **arr, int len);
void					del_map(t_map *map);
t_image					*del_image(t_game *game, t_image *img);
t_game					*del_game(t_game **agame, int i);
t_game					*init(char *title, t_map *map);
int						validate(char *file, t_map *map);

int						ft_help(void);
int						ft_out(int key);

int						hook_keydown(int key, t_game *game);
int						hook_keyup(int key, t_game *game);
int						hook_mousedown(int button, int x, int y, t_game *game);
int						hook_mousemove(int x, int y, t_game *game);

#endif
