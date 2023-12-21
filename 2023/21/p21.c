/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p21.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/21 18:57:38 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define WIDTH 131 //131
#define HEIGHT 131

#define ODD 0
#define EVEN 13
#define WW 1
#define EE 2
#define NN 3
#define SS 4
#define NW 5
#define NE 6
#define SW 7
#define SE 8
#define NW2 9
#define NE2 10
#define SW2 11
#define SE2 12

#define INPUT "input"

typedef struct s_ff
{
	char	name[4];
	int		state;
	int		signal;
	int		iter;
	char	**targets;
}	t_ff;

typedef struct s_con
{
	char	name[4];
	char	**source;
	int		received[50];
	int		signal;
	int		iter;
	char	**targets;
}	t_con;

typedef struct s_broadcast
{
	int		signal;
	char	**targets;
}	t_broadcast;

typedef struct s_signal
{
	char	from[4];
	char	to[4];
	int		signal;
}	t_signal;

void	ok_resetmap(char src[HEIGHT][WIDTH], char tgt[HEIGHT][WIDTH])
{
	int	j;
	int	i;

	j = 0;
	while (j < HEIGHT)
	{
		 i = 0;
		while (i < WIDTH)
		{
			if (src[j][i] == 'O')
				tgt[j][i] = '.';
			else
				tgt[j][i] = src[j][i];
			++i;
		}
		++j;
	}
}

void	ok_fillmap(char src[HEIGHT][WIDTH], char tgt[HEIGHT][WIDTH])
{
	int	j;
	int	i;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			if (src[j][i] == 'O')
			{
				tgt[j][i] = '.';
				if (i && src[j][i - 1] == '.')
					tgt[j][i - 1] = 'O';
				if (j && src[j - 1][i] == '.')
					tgt[j - 1][i] = 'O';
				if (i < WIDTH - 1 && src[j][i + 1] == '.')
					tgt[j][i + 1] = 'O';
				if (j < HEIGHT - 1 && src[j + 1][i] == '.')
					tgt[j + 1][i] = 'O';
			}
			++i;
		}
		++j;
	}
}

void	ok_copymap(char src[HEIGHT][WIDTH], char tgt[HEIGHT][WIDTH])
{
	int	j;
	int	i;

	j = 0;
	while (j < HEIGHT)
	{
		 i = 0;
		while (i < WIDTH)
		{
			tgt[j][i] = src[j][i];
			++i;
		}
		++j;
	}
}

void	ok_printmap(char src[HEIGHT][WIDTH])
{
	int	j;
	int	i;

	j = 0;
	while (j < HEIGHT)
	{
		 i = 0;
		while (i < WIDTH)
		{
			ft_printf("%c", src[j][i]);
			++i;
		}
		ft_printf("\n");
		++j;
	}
}

void	ok_process (char map1[HEIGHT][WIDTH], char map2[HEIGHT][WIDTH], int steps)
{
	int	step;

	step = 0;
	while (step < steps)
	{
		//ft_printf("processing %i\n", step);
		//ok_printmap(map1);
		ok_resetmap(map1, map2);
		ok_fillmap(map1, map2);
		ok_copymap(map2, map1);
		++step;
	}
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	long long	r;
	char		map1[HEIGHT][WIDTH];
	char		map2[HEIGHT][WIDTH];

	j = 0;
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			if (line[j][i] == 'S')
				line[j][i] = 'O';
			map1[j][i] = line[j][i];
			++i;
		}
		++j;
	}
	ok_process(map1, map2, 64);
	r = 0;
	//ft_put_split(line);
	//ok_printmap(map1);
	j = 0;
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			if (map1[j][i] == 'O')
				++r;
			++i;
		}
		++j;
	}
	*ptot = r;
}

void	ok_resetmap2(int src[14][HEIGHT][WIDTH], int tgt[14][HEIGHT][WIDTH], int type)
{
	int	j;
	int	i;

	j = 0;
	while (j < HEIGHT)
	{
		 i = 0;
		while (i < WIDTH)
		{
			if (src[type][j][i] > 0)
				tgt[type][j][i] = 0;
			else
				tgt[type][j][i] = src[type][j][i];
			++i;
		}
		++j;
	}
}

void	ok_copymap2(int src[14][HEIGHT][WIDTH], int tgt[14][HEIGHT][WIDTH], int type)
{
	int	j;
	int	i;

	j = 0;
	while (j < HEIGHT)
	{
		 i = 0;
		while (i < WIDTH)
		{
			tgt[type][j][i] = src[type][j][i];
			++i;
		}
		++j;
	}
}

void	ok_fillmap2(int src[14][HEIGHT][WIDTH], int tgt[14][HEIGHT][WIDTH], int type)
{
	int	j;
	int	i;
	//int	tmp[HEIGHT][WIDTH];

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			if (src[type][j][i] > 0)
			{
				tgt[type][j][i] = 0;
				if (i && src[type][j][i - 1] == 0)
					tgt[type][j][i - 1] = 1;
				if (j && src[type][j- 1][i] == 0)
					tgt[type][j- 1][i] = 1;
				if (i < WIDTH - 1 && src[type][j][i + 1] == 0)
					tgt[type][j][i + 1] = 1;
				if (j < HEIGHT - 1 && src[type][j+ 1][i] == 0)
					tgt[type][j+ 1][i] = 1;
			}
			++i;
		}
		++j;
	}
}

void	ok_printmap2(int src[14][HEIGHT][WIDTH], int type)
{
	int	j;
	int	i;

	j = 0;
	while (j < HEIGHT)
	{
		 i = 0;
		while (i < WIDTH)
		{
			ft_printf("%2i", src[type][j][i]);
			++i;
		}
		ft_printf("\n");
		++j;
	}
}

long long ok_evalmap2(int map1[14][HEIGHT][WIDTH], int map2[14][HEIGHT][WIDTH], int type, int steps)
{
	int			step;
	long long	r;
	int			i;
	int			j;

	step = 0;
	r = 0;
	while (step < steps)
	{
		ft_printf("processing %i\n", step);
		//ok_printmap2(map1, type);
		ok_resetmap2(map1, map2, type);
		ok_fillmap2(map1, map2, type);
		ok_copymap2(map2, map1, type);
		++step;
	}
	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			if (map2[type][j][i] > 0)
				++r;
			++i;
		}
		++j;
	}
	return (r);
}

void	ok_process2(int map1[14][HEIGHT][WIDTH], int map2[14][HEIGHT][WIDTH], long long r[14])
{
	map1[ODD][65][65] = 1;
	r[ODD] = ok_evalmap2(map1, map2, ODD, 261);
	map1[EVEN][65][65] = 1;
	r[EVEN] = ok_evalmap2(map1, map2, EVEN, 260);
	map1[NN][HEIGHT - 1][65] = 1;
	r[NN] = ok_evalmap2(map1, map2, NN, 130);
	map1[SS][0][65] = 1;
	r[SS] = ok_evalmap2(map1, map2, SS, 130);
	map1[WW][65][WIDTH - 1] = 1;
	r[WW] = ok_evalmap2(map1, map2, WW, 130);
	map1[EE][65][0] = 1;
	r[EE] = ok_evalmap2(map1, map2, EE, 130);
	map1[NE][HEIGHT - 1][0] = 1;
	r[NE] = ok_evalmap2(map1, map2, NE, 64);
	map1[NW][HEIGHT - 1][WIDTH - 1] = 1;
	r[NW] = ok_evalmap2(map1, map2, NW, 64);
	map1[SE][0][0] = 1;
	r[SE] = ok_evalmap2(map1, map2, SE, 64);
	map1[SW][0][WIDTH - 1] = 1;
	r[SW] = ok_evalmap2(map1, map2, SW, 64);
	map1[NE2][HEIGHT - 1][0] = 1;
	r[NE2] = ok_evalmap2(map1, map2, NE2, 131 + 64);
	map1[NW2][HEIGHT - 1][WIDTH - 1] = 1;
	r[NW2] = ok_evalmap2(map1, map2, NW2, 131 + 64);
	map1[SE2][0][0] = 1;
	r[SE2] = ok_evalmap2(map1, map2, SE2, 131 + 64);
	map1[SW2][0][WIDTH - 1] = 1;
	r[SW2] = ok_evalmap2(map1, map2, SW2, 131 + 64);
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	int			map1[14][HEIGHT][WIDTH];
	int			map2[14][HEIGHT][WIDTH];
	int			m;
	long long	r[14];
	m = 0;
	while (m < 14)
	{
		j = 0;
		while (line[j])
		{
			i = 0;
			while (line[j][i])
			{
				map1[m][j][i] = 0;
				map2[m][j][i] = 0;
				if (line[j][i] == '#')
				{
					map1[m][j][i] = -1;
					map2[m][j][i] = -1;
				}
				++i;
			}
			++j;
		}
		++m;
	}
	ok_process2(map1, map2, r);
	m = 0;
	while (m < 14)
	{
		ft_printf("r[%i] = %lli\n", m, r[m]);
		++m;
	}
	//ft_put_split(line);
	//ok_printmap(map1);
	*ptot = r[ODD] * (202299LL * 202299LL)
			+r[EVEN] * (202300LL * 202300LL)
			+ r[NN] + r[WW] + r[SS] + r[EE]
			+ 202300LL * (r[NE] + r[NW] + r[SE] + r[SW])
			+ 202299LL * (r[NE2] + r[NW2] + r[SE2] + r[SW2]);
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
