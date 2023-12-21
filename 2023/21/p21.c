/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p21.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/21 07:44:45 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define WIDTH 11 //131
#define HEIGHT 11

#define INPUT "inputtest"

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

void	ok_resetmap2(int src[HEIGHT][WIDTH], int tgt[HEIGHT][WIDTH])
{
	int	j;
	int	i;

	j = 0;
	while (j < HEIGHT)
	{
		 i = 0;
		while (i < WIDTH)
		{
			if (src[j][i] > 0)
				tgt[j][i] = 0;
			else
				tgt[j][i] = src[j][i];
			++i;
		}
		++j;
	}
}

void	ok_copymap2(int src[HEIGHT][WIDTH], int tgt[HEIGHT][WIDTH])
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

void	ok_fillmap2(int src[HEIGHT][WIDTH], int tgt[HEIGHT][WIDTH])
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
			if (src[j][i] >= 0 )
			{
				if (i > 0 && j > 0 && i < WIDTH - 1 && j < HEIGHT - 1)
					tgt[j][i] = 
			}
			++i;
		}
		++j;
	}
}

void	ok_printmap2(int src[HEIGHT][WIDTH])
{
	int	j;
	int	i;

	j = 0;
	while (j < HEIGHT)
	{
		 i = 0;
		while (i < WIDTH)
		{
			ft_printf("%2i", src[j][i]);
			++i;
		}
		ft_printf("\n");
		++j;
	}
}

void	ok_process2 (int map1[HEIGHT][WIDTH], int map2[HEIGHT][WIDTH], int steps)
{
	int	step;

	step = 0;
	while (step < steps)
	{
		ft_printf("processing %i\n", step);
		ok_printmap2(map1);
		ok_resetmap2(map1, map2);
		ok_fillmap2(map1, map2);
		ok_copymap2(map2, map1);
		++step;
	}
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	long long	r;
	int			map1[HEIGHT][WIDTH];
	int			map2[HEIGHT][WIDTH];

	j = 0;
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			map1[j][i] = 0;
			if (line[j][i] == 'O')
			{
				map1[j][i] = 1;
			}
			else
				map1[j][i] = 0;
			map2[j][i] = 0;
			if (line[j][i] == '#')
			{
				map1[j][i] = -1;
				map2[j][i] = -1;
			}
			++i;
		}
		++j;
	}
	ok_process2(map1, map2, 50);
	r = 0;
	//ft_put_split(line);
	//ok_printmap(map1);
	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			if (map2[j][i] > 0)
				r += (long long)map2[j][i];
			++i;
		}
		++j;
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
//797259120 low
//816870672 too low