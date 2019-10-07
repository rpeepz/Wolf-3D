/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 19:32:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/05 18:20:15 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		free_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->height)
	{
		free(map->cell[i]);
		i++;
	}
	free(map);
}

int			free_array(char **arr)
{
	int		i;

	i = 0;
	if (!arr)
		return (-42);
	while (arr[i])
		ft_strdel(&(arr[i++]));
	free(arr);
	return (-42);
}

static int	create_map(char *size, char *buf, t_map *map)
{
	char	**lines;
	char	**values;

	if (!(lines = ft_strsplit(buf, '\n')))
		return (-42);
	map->cell = malloc(sizeof(int *) * ft_atoi(size));
	map->height = -1;
	while (lines[++map->height])
	{
		if (!(values = ft_strsplit(lines[map->height], ' ')))
			return (free_array(lines));
		map->cell[map->height] =
			malloc(sizeof(int) * ft_atoi(ft_strchr(size, ' ')));
		map->width = -1;
		while (values[++map->width])
			map->cell[map->height][map->width] = ft_atoi(values[map->width]);
		free_array(values);
	}
	free_array(lines);
	return (1);
}

int			validate(char *filename, t_map *map)
{
	char	buf[PAGESIZE + 1];
	char	size[16];
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 3)
		return (-1);
	ft_bzero(buf, 16);
	ft_bzero(size, 16);
	while (1)
	{
		read(fd, buf, 1);
		if (*buf == '\n')
			break ;
		if (!ft_isdigit(*buf) && *buf != ' ')
			return (-2);
		ft_strncpy(&size[LEN(size)], buf, 1);
	}
	ft_bzero(buf, PAGESIZE + 1);
	read(fd, buf, 4096);
	close(fd);
	return (create_map(size, buf, map));
}
