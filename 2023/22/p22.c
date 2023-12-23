/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p22.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/22 18:55:47 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define WIDTH 10
#define LENGTH 10
#define HEIGHT 400

#define INPUT "inputtest"

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
	int		z;
	int		zd;
	int		supporting;
	int		width;
	int		length;
	int		height;
	int		above[100];
	int		below[100];
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
				if (!z)
					map[z][y][x] = 1;
				else
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

void	ok_printmap2(int map[HEIGHT][LENGTH][WIDTH], t_brick brick[1500])
{
	int	z;
	int	y;
	int	x;
	int	c;
	int	i;

	z = HEIGHT / 2 - 1;
	while (z >= 0)
	{
		y = 0;
		ft_printf("%3i|", z);
		while (y < LENGTH)
		{
			x = 0;
			while (x < WIDTH)
			{
				if (map[z][y][x])
				{
					i =  map[z][y][x];
					if (brick[i - 1].destroy == 1)
						c = (((i / 4) + 12 * i) % 64 + 192) << 16
						| ((32 + (i / 4) + 34 * i) % 64) << 8
						| (((i / 4) + i * 16) % 64);
					else
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
	z = 0;
	while (z < 10)
	{
		ft_printf("%3i\n", z);
		y = 0;
		while (y < LENGTH)
		{
			x = 0;
			while (x < WIDTH)
			{
				if (map[z][y][x])
				{
					i =  map[z][y][x];
					if (brick[i - 1].destroy == 1)
						c = (((i / 4) + 12 * i) % 64 + 192) << 16
						| ((32 + (i / 4) + 34 * i) % 64) << 8
						| (((i / 4) + i * 16) % 64);
					else
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
		ft_printf("\n");
		++z;
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
	z = 34;
	while (z < 38)
	{
		ft_printf("%3i\n", z);
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
					ft_printf("%.*^*C%4i%C", 0, c, map[z][y][x]);
				}
				else
					ft_printf("    ");
				++x;
			}
			ft_printf("\n");
			++y;
		}
		ft_printf("\n");
		++z;
	}
}

void	ok_inspectbrick(t_brick brick)
{
	int	i;

	ft_printf("brick id %4i,    destroy %i\n", brick.id, brick.destroy);
	ft_printf("x1 = %i, y1 = %i, z1 = %3i\n", brick.x1, brick.y1, brick.z1);
	ft_printf("x2 = %i, y2 = %i, z2 = %3i\n", brick.x2, brick.y2, brick.z2);
	ft_printf("w =  %i, l =  %i, h =  %3i\n", brick.width, brick.length, brick.height);
	i = 0;
	ft_printf("new z %3i, zd %3i, SUPPORTING %5i\n", brick.z, brick.zd, brick.supporting);
	ft_printf("Above: ");
	while (i < 100)
	{
		if (brick.above[i])
			ft_printf(" %4i ", brick.above[i]);
		++i;
	}
	ft_printf("\n");
	ft_printf("Below: ");
	i = 0;
	while (i < 100)
	{
		if (brick.below[i])
			ft_printf(" %4i ", brick.below[i]);
		++i;
	}
	ft_printf("\n");
}

int	ok_checkfall(int map[HEIGHT][LENGTH][WIDTH], int z, int y, int x)
{
	int	id;

	id = map[z][y][x];
	// if (id == 982)
	// {
	// 	ft_printf("check 982 z = %i\n", z);
	// }
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
	// if (id == 982)
	// {
	// 	ft_printf("fall 982 z = %i\n", z);
	// }
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
		z = f;
		f = 0;
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
						// if (z < 2)
						// 	ft_printf("zzz %i\n");
						if (!((x && map[z][y][x] == map[z][y][x - 1]) || (y && map[z][y][x] == map[z][y - 1][x])))
						{
							if (ok_checkfall(map, z, y, x))
							{
								ok_fallbrick(map, z, y, x);
								if(!f)
									f = z;
							}
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

int	ok_supported(int map[HEIGHT][LENGTH][WIDTH], int z, int id)
{
	int	x;
	int	y;
	int	below;

	if (!id)
		return (1);
	y = 0;
	if (id == 982)
		ft_printf("982\n");
	if (id == 378)
		ft_printf("378\n");
	below = 0;
	while (y < LENGTH)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (map[z][y][x] == id && map[z - 1][y][x] && !below)
			{
				below = map[z - 1][y][x];
			}
			else if (map[z][y][x] == id && map[z - 1][y][x] && map[z - 1][y][x] != below)
				return (1);
			++x;
		}
		++y;
	}
	if (id == 982)
		ft_printf("982 not supported %i\n", below);
	if (id == 378)
		ft_printf("378 not supported %i\n", below);
	return (0);
}

int	ok_checkbrick(int map[HEIGHT][LENGTH][WIDTH], int z, int y, int x)
{
	int	id;
	int	above[10];
	int	i;

	id = map[z][y][x];
	//check bricks above if they have different support
	if (id == 982)
		ft_printf("check 982\n");
	if (id == 378)
		ft_printf(" check 378\n");
	if (map[z + 1][y][x] == id)
		return (ok_checkbrick(map, z + 1, y, x));
	i = 0;
	while (i < 10)
	{
		above[i] = 0;
		++i;
	}
	i = 0;
	while (x + i < WIDTH - 1 && id == map[z][y][x + i])
	{
		// if (id == 982)
		// 	ft_printf("check x982 %i\n", i);
		above[i] = map[z + 1][y][x + i];
		++i;
	}
	while (y + i < LENGTH - 1 && id == map[z][y + i][x])
	{
		// if (id == 982)
		// 	ft_printf("check y982 %i y %i\n", i, y);
		above[i] = map[z + 1][y + i][x];
		// if (id == 982)
		// 	ft_printf("check y982 y + 1 %i map %i\n", y + 1, map[z][y + i][x]);
		// if (id == 982)
		// 	ft_printf("Condition1 %i %i total %i\n", y + i < LENGTH - 1, id == map[z][y + i][x], y + i < LENGTH - 1 && id == map[z][y + i][x]);
		++i;
		// if (id == 982)
		// 	ft_printf("Condition2  %i %i total %i\n", y + i < LENGTH - 1, id == map[z][y + i][x], y + i < LENGTH - 1 && id == map[z][y + i][x]);
	}
	i = 0;
	while (i < 10)
	{
		if (!ok_supported(map, z + 1, above[i]))
			return (0);
		++i;
	}
	return (1);
}

void	ok_checkbricks(int map[HEIGHT][LENGTH][WIDTH], t_brick brick[1500])
{
	int	z;
	int	y;
	int	x;

	z = 0;
	while (z < HEIGHT)
	{
		y = 0;
		while (y < LENGTH)
		{
			x = 0;
			while (x < WIDTH)
			{
				if (map[z][y][x] && !brick[map[z][y][x] - 1].destroy)
				{
					//check if brick can fall
					//fall brick and set f if f is not set
					// if (z < 2)
					// 	ft_printf("zzz %i\n");
					if (ok_checkbrick(map, z, y, x))
					{
						brick[map[z][y][x] - 1].destroy = 1;
					}
					else
						brick[map[z][y][x] - 1].destroy = -1;
				}
				++x;
			}
			++y;
		}
		++z;
	}
}

void	ok_fillbricks(int map[HEIGHT][LENGTH][WIDTH], t_brick brick[1500])
{
	int	z;
	int	y;
	int	x;
	int	id;

	z = 0;
	while (z < HEIGHT - 1)
	{
		y = 0;
		while (y < LENGTH)
		{
			x = 0;
			while (x < WIDTH)
			{
				if (map[z][y][x])
				{
					id = map[z][y][x];
					if (map[z + 1][y][x] != id)
						brick[id - 1].above[y * 10 + x] = map[z + 1][y][x];
					if (z && map[z - 1][y][x] != id)
						brick[id - 1].below[y * 10 + x] = map[z - 1][y][x];
				}
				++x;
			}
			++y;
		}
		++z;
	}
}

long long	ok_count(t_brick brick[1500])
{
	long long	r;
	int			i;

	r = 0;
	i = 0;
	while (brick[i].id)
	{
		if (brick[i].destroy == 1)
			++r;
		++i;
	}
	return (r);
}

void	ok_checkbricks2(t_brick brick[1500])
{
	int	i;
	int	j;
	int	k;

	i = 1;
	while (brick[i].id)
	{
		j = 0;
		while (j < 100)
		{
			if (brick[i].above[j])
			{
				k = 0;
				brick[i].destroy = -1;
				while (k < 100)
				{
					if (brick[brick[i].above[j] - 1].below[k] && brick[brick[i].above[j] - 1].below[k] != brick[i].id)
						brick[i].destroy = 1;
					++k;
				}
				if (brick[i].destroy == -1)
					break ;
			}
			++j;
		}
		if (!brick[i].destroy)
			brick[i].destroy = 1;
		++i;
	}
}

long long	ok_process(int map[HEIGHT][LENGTH][WIDTH], t_brick brick[1500])
{
	long long	r;

	//fill map first zeroes, then bricks
	ok_fillmap(map, brick);
	ok_printmap(map);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	//ok_fallbricks(map, brick);
	ok_fillbricks(map, brick);
	//check for destruction
	//ok_checkbricks(map, brick);
	ok_checkbricks2(brick);
	ok_printmap2(map, brick);
	ok_inspectbrick(brick[0]);
	ok_inspectbrick(brick[1319]);
	ok_inspectbrick(brick[958]);
	r = 0;
	//count bricks that can be destroyed;
	r = ok_count(brick);
	return (r);
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	int			map[HEIGHT][LENGTH][WIDTH];
	t_brick		brick[1500];
	long long	r;

	brick[0].id = 1;
	brick[0].destroy = 0;
	brick[0].x1 = 0;
	brick[0].y1 = 0;
	brick[0].z1 = 0;
	i = 0;
	while (line[j][i] != '~')
		++i;
	++i;
	brick[0].x2 = 9;
	brick[0].y2 = 9;
	brick[0].z2 = 0;
	brick[0].width = brick[0].x2 - brick[0].x1;
	brick[0].length = brick[0].y2 - brick[0].y1;
	brick[0].height = brick[0].z2 - brick[0].z1;
	i = 0;
	brick[0].z = 0;
	brick[0].zd = 0;
	while (i < 100)
	{
		brick[0].above[i] = 0;
		brick[0].below[i] = 0;
		++i;
	}
	j = 0;
	while (line[j])
	{
		brick[j + 1].id = j + 2;
		brick[j + 1].destroy = 0;
		brick[j + 1].x1 = ft_atoi(&line[j][0]);
		brick[j + 1].y1 = ft_atoi(&line[j][2]);
		brick[j + 1].z1 = ft_atoi(&line[j][4]);
		i = 0;
		while (line[j][i] != '~')
			++i;
		++i;
		brick[j + 1].x2 = ft_atoi(&line[j][i]);
		brick[j + 1].y2 = ft_atoi(&line[j][i + 2]);
		brick[j + 1].z2 = ft_atoi(&line[j][i + 4]);
		brick[j + 1].width = brick[j + 1].x2 - brick[j + 1].x1;
		brick[j + 1].length = brick[j + 1].y2 - brick[j + 1].y1;
		brick[j + 1].height = brick[j + 1].z2 - brick[j + 1].z1;
		i = 0;
		brick[j + 1].z = 0;
		brick[j + 1].zd = 0;
		while (i < 100)
		{
			brick[j + 1].above[i] = 0;
			brick[j + 1].below[i] = 0;
			++i;
		}
		++j;
	}
	brick[j + 1].id = 0;
	// print bricks;
	r = ok_process(map, brick);
	*ptot = r;
}

void	ok_sortbricks(t_brick brick[1500])
{
	int	i;
	int	j;
	int	s;
	int	tmp;

	j = 0;
	while (brick[j].id)
	{
		s = 1;
		while (s)
		{
			s = 0;
			i = 0;
			while (i < LENGTH * WIDTH - 1)
			{
				if (brick[j].above[i] < brick[j].above[i + 1])
				{
					tmp = brick[j].above[i];
					brick[j].above[i] = brick[j].above[i + 1];
					brick[j].above[i + 1] = tmp;
					s = 1;
				}
				if (brick[j].above[i] == brick[j].above[i + 1])
					brick[j].above[i + 1] = 0;
				++i;
			}
		}
		s = 1;
		while (s)
		{
			s = 0;
			i = 0;
			while (i < LENGTH * WIDTH - 1)
			{
				if (brick[j].below[i] < brick[j].below[i + 1])
				{
					tmp = brick[j].below[i];
					brick[j].below[i] = brick[j].below[i + 1];
					brick[j].below[i + 1] = tmp;
					s = 1;
				}
				if (brick[j].below[i] == brick[j].below[i + 1])
					brick[j].below[i + 1] = 0;
				++i;
			}
		}
		++j;
	}
}

void	ok_getz(int map[HEIGHT][LENGTH][WIDTH], t_brick brick[1500])
{
	int	z;
	int	y;
	int	x;
	int	id;

	z = 0;
	while(z < HEIGHT)
	{
		y = 0;
		while(y < LENGTH)
		{
			x = 0;
			while (x < WIDTH)
			{
				if (map[z][y][x])
				{
					id = map[z][y][x];
					brick[id - 1].z = z;
				}
				++x;
			}
			++y;
		}
		++z;
	}
}

void	ok_sortbelows(int belows[HEIGHT][100], int z)
{
	int	i;
	int	s;
	int	tmp;

	i = 0;
	s = 1;
	while (s)
	{
		s = 0;
		i = 0;
		while (i < 99)
		{
			if (belows[z][i] < belows[z][i + 1])
			{
				tmp = belows[z][i];
				belows[z][i] = belows[z][i + 1];
				belows[z][i + 1] = tmp;
				s = 1;
			}
			if (belows[z][i] && belows[z][i] == belows[z][i + 1])
			{
				belows[z][i + 1] = 0;
				s = 1;
			}
			++i;
		}
	}
}

void	ok_fillbelows(int belows[HEIGHT][100], int z, t_brick brick[1500])
{
	int	i;
	int	j;
	int	k;
	int	id;

	i = 0;
	j = 0;
	while (belows[z + 1][i])
	{
		id = belows[z + 1][i] - 1;
		if (brick[id].height && brick[brick[id].below[0] - 1].z < z)
		{
			belows[z][j] = belows[z + 1][i];
			++j;
		}
		else
		{
			k = 0;
			while (brick[id].below[k])
			{
				belows[z][j] = brick[id].below[k];
				++j;
				++k;
			}
		}
		++i;
	}
	ok_sortbelows(belows, z);
}

void	ok_getzd(int map[HEIGHT][LENGTH][WIDTH], t_brick brick[1500])
{
	int	i;
	int	j;
	int	z;
	int	belows[HEIGHT][100];

	i = 1;
	while (brick[i].id)
	{
		//ft_printf("zd %i\n", i);
		z = brick[i].z - 1;
		j = 0;
		while (brick[i].below[j])
		{
			belows[z][j] = brick[i].below[j];
			++j;
		}
		ok_sortbelows(belows, z);
		belows[z][j] = 0;
		while (belows[z][1])
		{
			--z;
			ok_fillbelows(belows, z, brick);
			if (!belows[z][0])
				ft_printf("FATA: ERROR\n");
		}
		brick[i].zd = z;
		++i;
	}
	(void)map;
}

void	ok_fillaboves(int aboves[HEIGHT][100], int z, t_brick brick[1500])
{
	int	i;
	int	j;
	int	k;
	int	id;

	i = 0;
	j = 0;
	while (aboves[z - 1][i])
	{
		id = aboves[z - 1][i] - 1;
		k = 0;
		while (brick[id].above[k])
		{
			aboves[z][j] = brick[id].above[k];
			++j;
			++k;
		}
		++i;
	}
	ok_sortbelows(aboves, z);
}

int	ok_count2(int uniques[1500], int z, t_brick brick[1500])
{
	int	r;
	int	k;
	int zz;

	zz = z;
	r = 0;
	k = 0;
	while (uniques[k])
	{
		if (brick[uniques[k] - 1].zd >= zz)
			++r;
		++k;
	}
	return (r);
}

void	ok_sortuniques(int uniques[1500])
{
	int	i;
	int	s;
	int	tmp;

	i = 0;
	s = 1;
	while (s)
	{
		s = 0;
		i = 0;
		while (i < 1499)
		{
			if (uniques[i] < uniques[i + 1])
			{
				tmp = uniques[i];
				uniques[i] = uniques[i + 1];
				uniques[i + 1] = tmp;
				s = 1;
			}
			if (uniques[i] && uniques[i] == uniques[i + 1])
			{
				uniques[i + 1] = 0;
				s = 1;
			}
			++i;
		}
	}
}

void	ok_filluniques(int uniques[1500], int z,int aboves[HEIGHT][100])
{
	int	i;
	int	k;

	i = 0;
	while (i < 1500)
		uniques[i++] = 0;
	while (aboves[z][0])
	{
		k = 0;
		while (aboves[z][k])
		{
			uniques[i] = aboves[z][k];
			++k;
			++i;
		}
		ok_sortuniques(uniques);
		i = 0;
		while (uniques[i])
			++i;
		++z;
	}
	uniques[i] = 0;
}

void	ok_getsupporting(t_brick brick[1500])
{
	int	i;
	int	j;
	int	z;
	int	aboves[HEIGHT][100];
	int	uniques[1500];

	i = 1;
	while (brick[i].id)
	{
		ft_printf("supp %i\n", i);
		z = brick[i].z + 1;
		j = 0;
		while (brick[i].above[j])
		{
			aboves[z][j] = brick[i].above[j];
			++j;
		}
		ok_sortbelows(aboves, z);
		aboves[z][j] = 0;
		while (aboves[z][0])
		{
			++z;
			aboves[z][0] = 0;
			ok_fillaboves(aboves, z, brick);
		}
		ok_filluniques(uniques, brick[i].z + 1, aboves);
		ft_printf("supp2 %i\n", i);
		brick[i].supporting = ok_count2(uniques, brick[i].z, brick);
		++i;
	}
}

long long	ok_count22(t_brick brick[1500])
{
	int			i;
	long long	r;

	i = 1;
	r = 0;
	while (brick[i].id)
	{
		r += (long long)brick[i].supporting;
		++i;
	}
	return (r);
}

long long	ok_process2(int map[HEIGHT][LENGTH][WIDTH], t_brick brick[1500])
{
	long long	r;

	//fill map first zeroes, then bricks
	ok_fillmap(map, brick);
	ok_printmap(map);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	ok_fallbricks(map, brick);
	//ok_fallbricks(map, brick);
	ok_fillbricks(map, brick);
	//check for destruction
	//ok_checkbricks(map, brick);
	ok_checkbricks2(brick);
	ok_printmap2(map, brick);
	ok_sortbricks(brick);

	ok_getz(map, brick);
	ok_getzd(map, brick);
	ok_getsupporting(brick);
	ok_inspectbrick(brick[958]);
	ok_inspectbrick(brick[0]);
	ok_inspectbrick(brick[798]);
	r = 0;
	while (r < 10)
	{
		ft_printf("HELLO\nWORLD!!!\n\n");
		ok_inspectbrick(brick[r]);
		++r;
	}
	ok_inspectbrick(brick[r]);
	//count bricks that can be destroyed;
	r = ok_count22(brick);
	return (r);
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	int			map[HEIGHT][LENGTH][WIDTH];
	t_brick		brick[1500];
	long long	r;

	brick[0].id = 1;
	brick[0].destroy = 0;
	brick[0].x1 = 0;
	brick[0].y1 = 0;
	brick[0].z1 = 0;
	i = 0;
	while (line[j][i] != '~')
		++i;
	++i;
	brick[0].x2 = 9;
	brick[0].y2 = 9;
	brick[0].z2 = 0;
	brick[0].width = brick[0].x2 - brick[0].x1;
	brick[0].length = brick[0].y2 - brick[0].y1;
	brick[0].height = brick[0].z2 - brick[0].z1;
	i = 0;
	brick[0].z = 0;
	brick[0].zd = 0;
	while (i < 100)
	{
		brick[0].above[i] = 0;
		brick[0].below[i] = 0;
		++i;
	}
	j = 0;
	while (line[j])
	{
		brick[j + 1].id = j + 2;
		brick[j + 1].destroy = 0;
		brick[j + 1].x1 = ft_atoi(&line[j][0]);
		brick[j + 1].y1 = ft_atoi(&line[j][2]);
		brick[j + 1].z1 = ft_atoi(&line[j][4]);
		i = 0;
		while (line[j][i] != '~')
			++i;
		++i;
		brick[j + 1].x2 = ft_atoi(&line[j][i]);
		brick[j + 1].y2 = ft_atoi(&line[j][i + 2]);
		brick[j + 1].z2 = ft_atoi(&line[j][i + 4]);
		brick[j + 1].width = brick[j + 1].x2 - brick[j + 1].x1;
		brick[j + 1].length = brick[j + 1].y2 - brick[j + 1].y1;
		brick[j + 1].height = brick[j + 1].z2 - brick[j + 1].z1;
		i = 0;
		brick[j + 1].z = 0;
		brick[j + 1].zd = 0;
		while (i < 100)
		{
			brick[j + 1].above[i] = 0;
			brick[j + 1].below[i] = 0;
			++i;
		}
		++j;
	}
	brick[j + 1].id = 0;
	// print bricks;
	r = ok_process2(map, brick);
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
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	ft_free_split(&line);
	return (0);
}

//719024 too high

//484 too low
//560 too high
//524 someone elses
//503