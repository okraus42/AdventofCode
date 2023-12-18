/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p17d.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by okraus            #+#    #+#             */
/*   Updated: 2023/12/18 13:55:43 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

//1 right, 2 left, 4 up, 8 down
#define STEP 40
#define HEIGHT 141
#define WIDTH 141

int ok_min(int heatmap[STEP][HEIGHT][WIDTH], int j, int i, int d)
{
	int	r;
	int	k;
	int	s;

	r = heatmap[0][j][i];
	k = 0;
	s = 0;
	while (k < STEP)
	{
		if (r > heatmap[k][j][i])
		{
			r = heatmap[k][j][i];
			s = k;
		}
		++k;
	}
	(void)d;
	ft_printf("|s%2i", s);
	return (r);
}

int	ok_checkvisited(int visited[STEP][HEIGHT][WIDTH])
{
	int	i;
	int	j;
	int	step;

	step = 0;
	while (step < STEP)
	{
		j = 0;
		while (j < HEIGHT)
		{
			i = 0;
			while(i < WIDTH)
			{
				if (!visited[step][j][i])
				{
					//ft_printf("not visited %2i %3i %3i\n", step, j, i);
					return (1);
				}
				++i;
			}
			++j;
		}
		++step;
	}
	return (0);
}

void ok_updateneighbours_left(char **line, int heatmap[STEP][HEIGHT][WIDTH], int visited[STEP][HEIGHT][WIDTH], int step, int j, int i)
{
	if (i <= 0 || step >= STEP || step % 4 == 1)
		return ;
	if (step % 4 == 3)
	{
		if (step < 36)
		{
			if (heatmap[step + 4][j][i - 1] > heatmap[step][j][i] + line[j][i - 1] - '0')
			{
				heatmap[step + 4][j][i - 1] = heatmap[step][j][i] + line[j][i - 1] - '0';
				//visited[step + 4][j][i - 1] = 0;
			}
		}
	}
	else if (step >= 12)
	{
		if (heatmap[3][j][i - 1] > heatmap[step][j][i] + line[j][i - 1] - '0')
		{
			heatmap[3][j][i - 1] = heatmap[step][j][i] + line[j][i - 1] - '0';
			//visited[1][j][i - 1] = 0;
		}
	}
	(void)visited;
	// if (j >= 0 && j <= 2 && i >= 4 && i <= 6)
	// 	ft_printf("L%i step %i %i %i %i %i\n", step, heatmap[step][j][i], j ,i, heatmap[3][j][i - 1], heatmap[step][j][i - 1]);
}

void ok_updateneighbours_right(char **line, int heatmap[STEP][HEIGHT][WIDTH], int visited[STEP][HEIGHT][WIDTH], int step, int j, int i)
{
	if (i >= WIDTH - 1 || step >= STEP || step % 4 == 3)
		return ;
	if (step % 4 == 1)
	{
		//ft_printf("11111 step %i  j=%2i   i=%2i    c%c %i\n", step, j, i, line[j][i + 1], heatmap[step][j][i]);
		if (step < 36)
		{
			//ft_printf("111 step %i c%c %i\n", step, line[j][i + 1], heatmap[step][j][i]);
			if (heatmap[step + 4][j][i + 1] > heatmap[step][j][i] + line[j][i + 1] - '0')
			{
				//ft_printf("1 step %i c%c %i\n", step, line[j][i + 1], heatmap[step][j][i]);
				heatmap[step + 4][j][i + 1] = heatmap[step][j][i] + line[j][i + 1] - '0';
				//ft_printf("1heatmap[%i][%i][%i] =  %i\n", step + 4, j, i + 1, heatmap[step + 4][j][i + 1]);
				//visited[step + 4][j][i + 1] = 0;
			}
		}
	}
	else if (step >= 12)
	{
		if (heatmap[1][j][i + 1] > heatmap[step][j][i] + line[j][i + 1] - '0')
		{
			//ft_printf("2 step %i %c %i\n", step, line[j][i + 1], heatmap[step][j][i]);
			heatmap[1][j][i + 1] = heatmap[step][j][i] + line[j][i + 1] - '0';
			//visited[1][j][i + 1] = 0;
		}
	}
	(void)visited;
	// if (j >= 0 && j <= 2 && i >= 4 && i <= 6)
	// 	ft_printf("R%i step %i %i %i %i %i\n", step, heatmap[step][j][i], j, i, heatmap[1][j][i + 1], heatmap[step][j][i + 1]);
}

void ok_updateneighbours_down(char **line, int heatmap[STEP][HEIGHT][WIDTH], int visited[STEP][HEIGHT][WIDTH], int step, int j, int i)
{
	if (j >= HEIGHT - 1 || step >= STEP || step % 4 == 2)
		return ;
	if (step % 4 == 0)
	{
		if (step < 36)
		{
			if (heatmap[step + 4][j + 1][i] > heatmap[step][j][i] + line[j + 1][i] - '0')
			{
				heatmap[step + 4][j + 1][i] = heatmap[step][j][i] + line[j + 1][i] - '0';
				//visited[step + 4][j + 1][i] = 0;
			}
		}
	}
	else if (step >= 12)
	{
		if (heatmap[0][j + 1][i] > heatmap[step][j][i] + line[j + 1][i] - '0')
		{
			heatmap[0][j + 1][i] = heatmap[step][j][i] + line[j + 1][i] - '0';
			//visited[1][j + 1][i] = 0;
		}
	}
	(void)visited;
	// if (j >= 0 && j <= 2 && i >= 4 && i <= 6)
	// 	ft_printf("D%i step %i %i %i %i %i\n", step, heatmap[step][j][i], j, i, heatmap[0][j + 1][i], heatmap[step][j + 1][i]);
}

void ok_updateneighbours_up(char **line, int heatmap[STEP][HEIGHT][WIDTH], int visited[STEP][HEIGHT][WIDTH], int step, int j, int i)
{
	if (j <= 0 || step >= STEP || step % 4 == 0)
		return ;
	if (step % 4 == 2)
	{
		if (step < 36)
		{
			if (heatmap[step + 4][j - 1][i] > heatmap[step][j][i] + line[j - 1][i] - '0')
			{
				heatmap[step + 4][j - 1][i] = heatmap[step][j][i] + line[j - 1][i] - '0';
				//visited[step + 4][j - 1][i] = 0;
			}
		}
	}
	else if (step >= 12)
	{
		if (heatmap[2][j - 1][i] > heatmap[step][j][i] + line[j - 1][i] - '0')
		{
			heatmap[2][j - 1][i] = heatmap[step][j][i] + line[j - 1][i] - '0';
			//visited[1][j - 1][i] = 0;
		}
	}
	(void)visited;
	// if (j >= 0 && j <= 2 && i >= 4 && i <= 6)
	// 	ft_printf("U%i step %i %i %i %i %i\n", step, heatmap[step][j][i], j, i, heatmap[2][j - 1][i], heatmap[step][j - 1][i]);
}

void ok_updateneighbours(char **line, int heatmap[STEP][HEIGHT][WIDTH], int visited[STEP][HEIGHT][WIDTH], int step, int j, int i)
{
	ok_updateneighbours_up(line, heatmap, visited, step, j, i);
	ok_updateneighbours_left(line, heatmap, visited, step, j, i);
	ok_updateneighbours_right(line, heatmap, visited, step, j, i);
	ok_updateneighbours_down(line, heatmap, visited, step, j, i);
}

void ok_updatelowest(char **line, int heatmap[STEP][HEIGHT][WIDTH], int visited[STEP][HEIGHT][WIDTH])
{
	int	i;
	int	j;
	int	step;
	int	min;
	int	mi;
	int mj;
	int ms;

	step = 0;
	min = 0x200000;
	ms = 0;
	mi = 0;
	mj = 0;
	while (step < STEP)
	{
		j = 0;
		while (j < HEIGHT)
		{
			i = 0;
			while(i < WIDTH)
			{
				if (!visited[step][j][i] && heatmap[step][j][i] < min)
				{
					min = heatmap[step][j][i];
					//ft_printf("min = %i\n", min);
					mi = i;
					mj = j;
					ms = step;
				}
				++i;
			}
			++j;
		}
		++step;
	}
	//ft_printf("VISIT %i\n", heatmap[ms][mj][mi]);
	ok_updateneighbours(line, heatmap, visited, ms, mj, mi);
	visited[ms][mj][mi] = 1;
	// if (mi >= 4 && mi <= 6 && mj >= 0 && mj <= 2)
	//ft_printf("visited %2i %3i %3i %5i\n", ms, mj, mi, heatmap[ms][mj][mi]);
	//ft_printf("visited %2i %3i %3i %5i\n", ms, mj, mi, heatmap[0][0][1]);
}

void	ok_fillheatmap(char **line, int heatmap[STEP][HEIGHT][WIDTH])
{
	int	i;
	int	j;
	int	step;
	int	visited[STEP][HEIGHT][WIDTH];

	step = 0;
	while (step < STEP)
	{
		j = 0;
		while (j < HEIGHT)
		{
			i = 0;
			while(i < WIDTH)
			{
				visited[step][j][i] = 0;
				++i;
			}
			++j;
		}
		++step;
	}
	step = 0;
	while (ok_checkvisited(visited))
	{
		ok_updatelowest(line, heatmap, visited);
	}
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	int			heatmap[STEP][HEIGHT][WIDTH];
	long long	r;
	int			steps;


	r = 0;
	j = 0;
	steps = 0;
	i = 0;
	line[0][0] = '0';
	while (steps < STEP)
	{
		j = 0;
		while (j < HEIGHT)
		{
			i = 0;
			while(i < WIDTH)
			{
				if (steps >= 36 && i == 0 && j == 0)
					heatmap[steps][j][i] = 0;
				else
					heatmap[steps][j][i] = 0x100000;
				++i;
				//ft_printf("%i\n", heatmap[steps][j][i - 1]);
			}
			++j;
		}
		++steps;
	}
	ok_fillheatmap(line, heatmap);
	i = 0;
	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while(i < WIDTH)
		{
			ft_printf("%4i ", ok_min(heatmap, j, i, 0));
			++i;
		}
		ft_printf("\n");
		++j;
	}
	r = heatmap[12][HEIGHT - 1][WIDTH - 1];
	 i = 0;
	while (i < STEP)
	{
		ft_printf("%2i %5i\n", i, heatmap[i][HEIGHT - 1][WIDTH - 1]);
		if (i >= 12 && r > heatmap[i][HEIGHT - 1][WIDTH - 1])
			r = heatmap[i][HEIGHT - 1][WIDTH- 1];
		++i;
	}
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
	line = ft_readfile("input", 65536);
	//lines = ft_split(line[0], '');
	//ft_printf("%p\n", (void *)line);
	//ft_printf("j = %i\n", j);
	i = 0;
	j = 0;
	//ok_update(line, &total[0], i, j);
	ft_printf("t1=%5lld\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	return (0);
}
