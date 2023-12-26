/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p23c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/26 19:22:44 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define WIDTH 10
#define LENGTH 10
#define HEIGHT 400

#define INPUT "inputtest"
#define LASTROW 140

#define ABS(a) ((a > 0) * a + (a < 0) * a)
#define PN(a) ((a > 0) - (a < 0))

#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3

typedef struct s_node
{
	int	type;
	int	visited;
	int	id;
	int	x;
	int	y;
	int	dir[4];
	int	dist[4];
}	t_node;
//16 bits step count 8 bits y, 8 bits x

//Depth first search?
//copy map
//index positions of crossroads
//calculate distances

t_node	ok_fill_nexus(char **line, int r, int y, int x)
{
	t_node	nex;

	if (line[y][x] == 'S')
	{
		nex.type = 1;
	}
	else if (line[y][x] == 'E')
	{
		nex.type = 5;
	}
	else if (line[y][x] == '.')
	{
		nex.type = 3;
	}
	nex.id = r;
	nex.x = x;
	nex.y = y;
	nex.visited = 0;
	nex.dir[0] = -1;
	nex.dir[1] = -1;
	nex.dir[2] = -1;
	nex.dir[3] = -1;
	return (nex);
}

void	ok_floodcount(int map[150][150], int step, int y, int x, char **line)
{
	int	c;

	if (map[y][x])
	{
		return ;
	}
	if (line[y][x] != '.')
	{
		if (line[y][x] != '#')
			map[y][x] = step;
		return ;
	}
	map[y][x] = step;
	c = 0;
	if (line[y - 1][x] == '.')
		++c;
	if (line[y + 1][x] == '.')
		++c;
	if (line[y][x - 1] == '.')
		++c;
	if (line[y][x + 1] == '.')
		++c;
	if (c > 2)
		return ;
	ok_floodcount(map, step + 1, y - 1, x, line);
	ok_floodcount(map, step + 1, y + 1, x, line);
	ok_floodcount(map, step + 1, y, x - 1, line);
	ok_floodcount(map, step + 1, y, x + 1, line);
}

int	ok_findnexus(t_node nexus[40], int y, int x)
{
	int	j;

	j = 0;
	while (j < 40)
	{
		if (nexus[j].y == y && nexus[j].x == x)
			return (j);
		++j;
	}
	ft_printf("nexus at y %i, x %i not found\n", y, x);
	return (-1);
}

void	ok_updatenex(t_node nexus[40], int j, int map[150][150])
{
	int	y;
	int	x;
	int	my[4];
	int	mx[4];
	int	max[4];

	my[0] = -1;
	mx[0] = -1;
	my[1] = -1;
	mx[1] = -1;
	my[2] = -1;
	mx[2] = -1;
	my[3] = -1;
	mx[3] = -1;
	max[0] = 0;
	max[1] = 0;
	max[2] = 0;
	max[3] = 0;
	y = 0;
	while (y < 150)
	{
		x = 0;
		while (x < 150)
		{
			if (map[y][x])
			{
				if (map[y][x] & 0x10000)
				{
					if (map[y][x] > max[0])
					{
						max[0] = map[y][x];
						my[0] = y;
						mx[0] = x;
					}
				}
				else if (map[y][x] & 0x20000)
				{
					if (map[y][x] > max[1])
					{
						max[1] = map[y][x];
						my[1] = y;
						mx[1] = x;
					}
				}
				else if (map[y][x] & 0x40000)
				{
					if (map[y][x] > max[2])
					{
						max[2] = map[y][x];
						my[2] = y;
						mx[2] = x;
					}
				}
				else if (map[y][x] & 0x80000)
				{
					if (map[y][x] > max[3])
					{
						max[3] = map[y][x];
						my[3] = y;
						mx[3] = x;
					}
				}
			}
			++x;
		}
		++y;
	}
	if (max[0])
	{
		nexus[j].dir[0] = ok_findnexus(nexus, my[0], mx[0]);
		nexus[j].dist[0] = max[0] & 0xFFFF;
	}
	if (max[1])
	{
		nexus[j].dir[1] = ok_findnexus(nexus, my[1], mx[1]);
		nexus[j].dist[1] = max[1] & 0xFFFF;
	}
	if (max[2])
	{
		nexus[j].dir[2] = ok_findnexus(nexus, my[2], mx[2]);
		nexus[j].dist[2] = max[2] & 0xFFFF;
	}
	if (max[3])
	{
		nexus[j].dir[3] = ok_findnexus(nexus, my[3], mx[3]);
		nexus[j].dist[3] = max[3] & 0xFFFF;
	}
}

void	ok_fillnodes(char **line, t_node nexus[40])
{
	int	map[150][150];
	int	y;
	int	x;
	int	j;

	j = 0;
	while (nexus[j].type)
	{
		y = 0;
		while (y < 150)
		{
			x = 0;
			while (x < 150)
			{
				map[y][x] = 0;
				++x;
			}
			++y;
		}
		if (j == 0)
		{
			ft_printf("first node\n");
			ok_floodcount(map, 0x20001, nexus[j].y + 1, nexus[j].x, line);
			ok_updatenex(nexus, j, map);
		}
		else if(nexus[j].type == 5)
		{
			ft_printf("last node\n");
			ok_floodcount(map, 0x10001, nexus[j].y - 1, nexus[j].x, line);
			ok_updatenex(nexus, j, map);
		}
		else
		{
			ok_floodcount(map, 0x10001, nexus[j].y - 1, nexus[j].x, line);
			ok_floodcount(map, 0x20001, nexus[j].y + 1, nexus[j].x, line);
			ok_floodcount(map, 0x40001, nexus[j].y, nexus[j].x - 1, line);
			ok_floodcount(map, 0x80001, nexus[j].y, nexus[j].x + 1, line);
			ok_updatenex(nexus, j, map);
		}
		++j;
	}
	//ft_put_split(line);
	//clear map
	//start from one node and fill the map with steps till the next node.
}

void	ok_free_nodes(t_node ***nexus)
{
	int		i;
	t_node	**nex;

	i = 0;
	nex = *nexus;
	if (!(nex))
		return ;
	while (i < 40)
	{
		free(nex[i]);
		++i;
	}
	free(nex);
	*nex = NULL;
}

void	ok_visitall(t_node **nexus, int n, int steps, int *r)
{
	t_node	**nex;
	int		i;
	int		j;

	ft_printf("visiting %p %2i, steps %i, r %i\n", nexus, n, steps, *r);
	nex = NULL;
	if (nexus[n]->visited)
	{
		i = 0;
	}
	else if (nexus[n]->type == 5)
	{
		if (steps > *r)
			*r = steps;
	}
	else
	{
		i = 0;
		nex = ft_calloc(sizeof(t_node *), 40);
		ft_printf("creating %p\n", nex);
		while (i < 40)
		{
			nex[i] = ft_calloc(sizeof(t_node), 1);
			nex[i]->id = nexus[i]->id;
			nex[i]->type = nexus[i]->type;
			nex[i]->visited = nexus[i]->visited;
			j = 0;
			while (j < 4)
			{
				nex[i]->dir[j] = nexus[i]->dir[j];
				nex[i]->dist[j] = nexus[i]->dist[j];
				++j;
			}
			++i;
		}
		nex[n]->visited = 1;
		j = 0;
		while (j < 4)
		{
			if (nex[n]->dir[j] >= 0)
				ok_visitall(nex, nex[n]->dir[j], steps + (nex[n]->dist[j] & 0xffff), r);
			++j;
		}
	}
	//i do not know how to recursively free :()
	ft_printf("freeing  %p \n", nex);
	ok_free_nodes(&nex);
}

long long	ok_magic(char **line)
{
	int	x;
	int	y;
	int	c;
	int	r;
	int	i;
	int	j;
	t_node	nexus[40];  //36 should be enough
	t_node	**nex;
	//create start and end nodes
	//create nodes for crossroads
	//calculate distances and connect nodes
	//find the longest path using nodes
	y = 1;
	r = 0;
	i = 0;
	while (i < 40)
	{
		nexus[i].type = 0;
		++i;
	}
	//fill nexus 0
	x = 0;
	while (line[0][x] != 'S')
	{
		++x;
	}
	nexus[0] = ok_fill_nexus(line, 0, 0, x);
	r = 1;
	while (line[y + 1])
	{
		x = 1;
		while (line[y][x + 1])
		{
			if (line[y][x] == '.')
			{
				c = 0;
				if (line[y - 1][x] == '.')
					++c;
				if (line[y + 1][x] == '.')
					++c;
				if (line[y][x - 1] == '.')
					++c;
				if (line[y][x + 1] == '.')
					++c;
				if (c >= 3)
				{
					nexus[r] = ok_fill_nexus(line, r, y, x);
					++r;
					ft_printf("%3i crossroad %i at y %3i, x %3i\n", r, c, y, x);
				}
				if (c == 1)
					ft_printf("deadend at y %3i, x %3i %c %c %c %c\n",y, x, line[y - 1][x], line[y + 1][x], line[y][x - 1], line[y][x + 1]);
			}
			++x;
		}
		++y;
	}
	x = 0;
	while (line[y][x] != 'E')
	{
		++x;
	}
	nexus[r] = ok_fill_nexus(line, r, y, x);
	++r;
	ok_fillnodes(line, nexus);
	x = 0;
	while (nexus[x].type)
	{
		ft_printf("nexus id %2i, type %i, y %3i, x %3i \n", nexus[x].id, nexus[x].type, nexus[x].y, nexus[x].x);
		if (nexus[x].dir[0] >= 0)
			ft_printf("0 dir %2i, dist %4i\n", nexus[x].dir[0], nexus[x].dist[0]);
		if (nexus[x].dir[1] >= 0)
			ft_printf("1 dir %2i, dist %4i\n", nexus[x].dir[1], nexus[x].dist[1]);
		if (nexus[x].dir[2] >= 0)
			ft_printf("2 dir %2i, dist %4i\n", nexus[x].dir[2], nexus[x].dist[2]);
		if (nexus[x].dir[3] >= 0)
			ft_printf("3 dir %2i, dist %4i\n", nexus[x].dir[3], nexus[x].dist[3]);
		++x;
	}
	r = 0;
	nexus[0].visited = 1;
	nex = malloc(sizeof(t_node *) * 40);
	i = 0;
	while (i < 40)
	{
		nex[i] = malloc(sizeof(t_node));
		nex[i]->id = nexus[i].id;
		nex[i]->type = nexus[i].type;
		nex[i]->visited = nexus[i].visited;
		j = 0;
		while (j < 4)
		{
			nex[i]->dir[j] = nexus[i].dir[j];
			nex[i]->dist[j] = nexus[i].dist[j];
			++j;
		}
		++i;
	}
	ok_visitall(nex, nex[0]->dir[1], nex[0]->dist[1], &r);
	ok_free_nodes(&nex);
	//recursion hell Depth first search through all nodes;
	//update type of node after start and update node before end;
	//check if the distances make sense
	return (r);
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	long long	r;

	j = 0;
	i = 0;
	while(line[j][i] != '.')
		i++;
	line[j][i] = 'S';
	while(line[j] && line[j + 1])
		++j;
	i = 0;
	while(line[j][i] != '.')
		i++;
	line[j][i] = 'E';
	j = 0;
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			if (line[j][i] == '>' || line[j][i] == '^' || line[j][i] == '<' || line[j][i] == 'v')
				line[j][i] = '.';
			++i;
		}
		++j;
	}
	r = 0;
	r = ok_magic(line);
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
	//ok_update(line, &total[0], i, j);
	ft_printf("t1=%5lld\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	ft_free_split(&line);
	return (0);
}

//14324 too high
//12356 too high
//9898 too high
// NEW r 4454, lc 0
// NEW r 4546, lc 7
// NEW r 4606, lc 15
// NEW r 4754, lc 20
// NEW r 4818, lc 47
// NEW r 4834, lc 66
// NEW r 4910, lc 79
// NEW r 4978, lc 93
// NEW r 5038, lc 99
// NEW r 5186, lc 104
// NEW r 5218, lc 163
// NEW r 5366, lc 168
// NEW r 5614, lc 2730
// NEW r 5622, lc 2793
// NEW r 5782, lc 3356
//6514 eats all memory though