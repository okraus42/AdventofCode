/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p22.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/22 08:30:31 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define WIDTH 10
#define LENGTH 10
#define HEIGHT 400

#define INPUT "input"

#define ABS(a) ((a > 0) * a + (a < 0) * a)
#define PN(a) ((a > 0) - (a < 0))

typedef struct s_brick
{
	int		id;
	int		destroy;
	int		x1;
	int		y1;
	int		z1;
	int		x2;
	int		y2;
	int		z2;
	int		width;
	int		length;
	int		height;
}	t_brick;

void	ok_fillmap(int map[HEIGHT][LENGTH][WIDTH], t_brick brick[1500])
{
	int	z;
	int	y;
	int	x;
	int	b;
	int	i;

	z = 0;
	while (z < HEIGHT)
	{
		y = 0;
		while (y < LENGTH)
		{
			x = 0;
			while (x < WIDTH)
			{
				map[z][y][x] = 0;
				++x;
			}
			++y;
		}
		++z;
	}
	b = 0;
	while(brick[b].id)
	{
		map[brick[b].z1][brick[b].y1][brick[b].x1] = brick[b].id;
		i = 1;
		while (i <= ABS(brick[b].height))
		{
			map[brick[b].z1 + (i * PN(brick[b].height))][brick[b].y1][brick[b].x1] = brick[b].id;
			++i;
		}
		while (i <= ABS(brick[b].length))
		{
			map[brick[b].z1][brick[b].y1 + (i * PN(brick[b].length))][brick[b].x1] = brick[b].id;
			++i;
		}
		while (i <= ABS(brick[b].width))
		{
			map[brick[b].z1][brick[b].y1][brick[b].x1 + (i * PN(brick[b].width))] = brick[b].id;
			++i;
		}
		++b;
	}
}

void	ok_printmap(int map[HEIGHT][LENGTH][WIDTH])
{
	int	z;
	int	y;
	int	x;
	int	c;
	int	i;

	z = HEIGHT - 1;
	while (z >= 0)
	{
		y = 0;
		while (y < LENGTH)
		{
			x = 0;
			while (x < WIDTH)
			{
				if (map[z][y][x])
				{
					i =  map[z][y][x];
					c = (((i / 4) + 12 * i) % 64 + 192) << 16
						| ((32 + (i / 4) + 34 * i) % 64 + 192) << 8
						| (((i / 4) + i * 16) % 64 + 192);
					ft_printf("%.*^*C%i%C", 0, c, map[z][y][x] % 10);
				}
				else
					ft_printf(" ");
				++x;
			}
			ft_printf("|");
			++y;
		}
		ft_printf("\n");
		--z;
	}
	y = 0;
	z = 1;
	while (y < LENGTH)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (map[z][y][x])
			{
				i =  map[z][y][x];
				c = (((i / 4) + 12 * i) % 64 + 192) << 16
					| ((32 + (i / 4) + 34 * i) % 64 + 192) << 8
					| (((i / 4) + i * 16) % 64 + 192);
				ft_printf("%.*^*C%4i%C", 0, c, map[z][y][x]);
			}
			else
				ft_printf("    ");
			++x;
		}
		ft_printf("\n");
		++y;
	}
}

void	ok_inspectbrick(t_brick brick)
{
	ft_printf("brick id %4i,    destroy %i\n", brick.id, brick.destroy);
	ft_printf("x1 = %i, y1 = %i, z1 = %3i\n", brick.x1, brick.y1, brick.z1);
	ft_printf("x2 = %i, y2 = %i, z2 = %3i\n", brick.x2, brick.y2, brick.z2);
	ft_printf("w =  %i, l =  %i, h =  %3i\n", brick.width, brick.length, brick.height);
	ft_printf("PN(brick.width) %i\n", PN(brick.width));
}

int	ok_checkfall(int map[HEIGHT][LENGTH][WIDTH], int z, int y, int x)
{
	int	id;

	id = map[z][y][x];
	if (map[z - 1][y][x])
		return (0);
	if (x < WIDTH - 1 && id == map[z][y][x + 1])
		return (ok_checkfall(map, z, y, x + 1));
	if (y < LENGTH - 1 && id == map[z][y + 1][x])
		return (ok_checkfall(map, z, y + 1, x));
	return (1);
}

void	ok_fallbrick(int map[HEIGHT][LENGTH][WIDTH], int z, int y, int x)
{
	int	id;

	id = map[z][y][x];
	map[z - 1][y][x] = id;
	map[z][y][x] = 0;

	if (x < WIDTH - 1 && id == map[z][y][x + 1])
		ok_fallbrick(map, z, y, x + 1);
	if (y < LENGTH - 1 && id == map[z][y + 1][x])
		ok_fallbrick(map, z, y + 1, x);
	if (z < HEIGHT - 1 && id == map[z + 1][y][x])
		ok_fallbrick(map, z + 1, y, x);
}

void	ok_fallbricks(int map[HEIGHT][LENGTH][WIDTH], t_brick brick[1500])
{
	int	z;
	int	y;
	int	x;
	int	f;

	f = 2; //first level where something falls, could add last level with brick for optimization
	while (f)
	{
		f = 0;
		z = f;
		while (z < HEIGHT)
		{
			y = 0;
			while (y < LENGTH)
			{
				x = 0;
				while (x < WIDTH)
				{
					if (map[z][y][x])
					{
						//check if brick can fall
						//fall brick and set f if f is not set
						if (ok_checkfall(map, z, y, x))
						{
							ok_fallbrick(map, z, y, x);
							if(!f)
								f = z;
						}
					}
					++x;
				}
				++y;
			}
			++z;
		}
	}
	(void)brick;
}

long long	ok_process(int map[HEIGHT][LENGTH][WIDTH], t_brick brick[1500])
{
	long long	r;

	//fill map first zeroes, then bricks
	ok_fillmap(map, brick);
	ok_printmap(map);
	ok_inspectbrick(brick[151]);
	ok_inspectbrick(brick[305]);
	ok_inspectbrick(brick[1062]);
	ok_inspectbrick(brick[677]);
	ok_inspectbrick(brick[451]);
	ok_inspectbrick(brick[438]);
	ok_fallbricks(map, brick);
	ok_printmap(map);
	//check
	r = 0;
	return (r);
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	int			map[HEIGHT][LENGTH][WIDTH];
	t_brick		brick[1500];
	long long	r;

	j = 0;
	while (line[j])
	{
		brick[j].id = j + 1;
		brick[j].destroy = 0;
		brick[j].x1 = ft_atoi(&line[j][0]);
		brick[j].y1 = ft_atoi(&line[j][2]);
		brick[j].z1 = ft_atoi(&line[j][4]);
		i = 0;
		while (line[j][i] != '~')
			++i;
		++i;
		brick[j].x2 = ft_atoi(&line[j][i]);
		brick[j].y2 = ft_atoi(&line[j][i + 2]);
		brick[j].z2 = ft_atoi(&line[j][i + 4]);
		brick[j].width = brick[j].x2 - brick[j].x1;
		brick[j].length = brick[j].y2 - brick[j].y1;
		brick[j].height = brick[j].z2 - brick[j].z1;
		++j;
	}
	brick[j].id = 0;
	// print bricks;
	r = ok_process(map, brick);
	*ptot = r;
}

int	main(void)
{
	char		**line;
	//char		**lines;
	int			i;
	int			j;
	long long	total[2];

	total[0] = 0;
	total[1] = 0;
	line = NULL;
	i = 1;
	line = ft_readfile(INPUT, 65536);
	//lines = ft_split(line[0], '');
	//ft_printf("%p\n", (void *)line);
	//ft_printf("j = %i\n", j);
	i = 0;
	j = 0;
	ok_update(line, &total[0], i, j);
	ft_printf("t1=%5lld\n", total[0]);
	//ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	ft_free_split(&line);
	return (0);
}
