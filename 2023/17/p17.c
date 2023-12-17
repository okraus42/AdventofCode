/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p17.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/17 13:49:51 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

//1 right, 2 left, 4 up, 8 down
void	ok_fillheatmap_left(char** line, int heatmap[141][141], int i, int j, int steps, int heat);
void	ok_fillheatmap_right(char** line, int heatmap[141][141], int i, int j, int steps, int heat);
void	ok_fillheatmap_up(char** line, int heatmap[141][141], int i, int j, int steps, int heat);
void	ok_fillheatmap_down(char** line, int heatmap[141][141], int i, int j, int steps, int heat);

void	ok_fillheatmap_right(char** line, int heatmap[141][141], int i, int j, int steps, int heat)
{
	int	heat2;
	static int ij;

	if (i + j > ij)
	{
		ij = i + j;
		ft_printf("R%i ij, heat %i\n", ij, heat);
	}
	if (i < 0 || i >= 141 || j < 0 || j >= 141 || heat > 1350 || (heatmap[j][i] && heatmap[j][i] <= -steps + heat + line[j][i] - '0'))
		return ;
	heat2 = heat + line[j][i] - '0';
	if (!heatmap[j][i] || heat2 <= heatmap[j][i])
	{
		heatmap[j][i] = heat2;
		if (heat2 < 1282 && j == 141 - 1 && i == 141 - 1)
			ft_printf("current solution %i\n", heat2);
	}
	// else
	// 	ft_printf("WTF\n");
	//ft_printf("processing right %i %i %c %i \n", i, j, line[j][i], heatmap[j][i]);
	ok_fillheatmap_up(line, heatmap, i, j - 1, steps, heat2);
	if (j > 0)
	{
		heat = heat2 + line[j - 1][i] - '0';
		ok_fillheatmap_up(line, heatmap, i, j - 2, steps, heat);
	}
	if (j > 1)
	{
		heat = heat2 + line[j - 1][i] - '0' + line[j - 2][i] - '0';
		ok_fillheatmap_up(line, heatmap, i, j - 3, steps, heat);
	}
	ok_fillheatmap_down(line, heatmap, i, j + 1, steps, heat2);
	if (j < 141 - 1)
	{
		heat = heat2 + line[j + 1][i] - '0';
		ok_fillheatmap_down(line, heatmap, i, j + 2, steps, heat);
	}
	if (j <  141 - 2)
	{
		heat = heat2 + line[j + 1][i] - '0' + line[j + 2][i] - '0';
		ok_fillheatmap_down(line, heatmap, i, j + 3, steps, heat);
	}
}

void	ok_fillheatmap_left(char** line, int heatmap[141][141], int i, int j, int steps, int heat)
{
	int	heat2;
	static int ij;

	if (i + j > ij)
	{
		ij = i + j;
		ft_printf("L%i ij, heat %i\n", ij, heat);
	}
	if (i < 0 || i >= 141 || j < 0 || j >= 141 || heat > 1350 || (heatmap[j][i] && heatmap[j][i] <= -steps + heat + line[j][i] - '0'))
		return ;
	heat2 = heat + line[j][i] - '0';
	if (!heatmap[j][i] || heat2 <= heatmap[j][i])
	{
		heatmap[j][i] = heat2;
		// if (heat2 < 1500 && j == 141 - 1 && i == 141 - 1)
		// 	ft_printf("current solution %i\n", heat2);
	}
	// else
	// 	ft_printf("WTF\n");
	//ft_printf("processing right %i %i %c %i \n", i, j, line[j][i], heatmap[j][i]);
	ok_fillheatmap_up(line, heatmap, i, j - 1, steps, heat2);
	if (j > 0)
	{
		heat = heat2 + line[j - 1][i] - '0';
		ok_fillheatmap_up(line, heatmap, i, j - 2, steps, heat);
	}
	if (j > 1)
	{
		heat = heat2 + line[j - 1][i] - '0' + line[j - 2][i] - '0';
		ok_fillheatmap_up(line, heatmap, i, j - 3, steps, heat);
	}
	ok_fillheatmap_down(line, heatmap, i, j + 1, steps, heat2);
	if (j < 141 - 1)
	{
		heat = heat2 + line[j + 1][i] - '0';
		ok_fillheatmap_down(line, heatmap, i, j + 2, steps, heat);
	}
	if (j <  141 - 2)
	{
		heat = heat2 + line[j + 1][i] - '0' + line[j + 2][i] - '0';
		ok_fillheatmap_down(line, heatmap, i, j + 3, steps, heat);
	}
}

void	ok_fillheatmap_up(char** line, int heatmap[141][141], int i, int j, int steps, int heat)
{
	int	heat2;
	static int ij;

	if (i + j > ij)
	{
		ij = i + j;
		ft_printf("U%i ij, heat %i\n", ij, heat);
	}
	if (i < 0 || i >= 141 || j < 0 || j >= 141 || heat > 1350 || (heatmap[j][i] && heatmap[j][i] <= -steps + heat + line[j][i] - '0'))
		return ;
	heat2 = heat + line[j][i] - '0';
	if (!heatmap[j][i] || heat2 <= heatmap[j][i])
	{
		heatmap[j][i] = heat2;
		// if (heat2 < 1500 && j == 141 - 1 && i == 141 - 1)
		// 	ft_printf("current solution %i\n", heat2);
	}
	// else
	// 	ft_printf("WTF\n");
	//ft_printf("processing right %i %i %c %i \n", i, j, line[j][i], heatmap[j][i]);
	ok_fillheatmap_left(line, heatmap, i - 1, j, steps, heat2);
	if (i > 0)
	{
		heat = heat2 + line[j][i - 1] - '0';
		ok_fillheatmap_left(line, heatmap, i - 2, j, steps, heat);
	}
	if (i > 1)
	{
		heat = heat2 + line[j][i - 1] - '0' + line[j][i - 2] - '0';
		ok_fillheatmap_left(line, heatmap, i - 3, j, steps, heat);
	}
	ok_fillheatmap_right(line, heatmap, i + 1, j, steps, heat2);
	if (i < 141 - 1)
	{
		heat = heat2 + line[j][i + 1] - '0';
		ok_fillheatmap_right(line, heatmap, i + 2, j, steps, heat);
	}
	if (i <  141 - 2)
	{
		heat = heat2 + line[j][i + 1] - '0' + line[j][i + 2] - '0';
		ok_fillheatmap_right(line, heatmap, i + 3, j, steps, heat);
	}
}


void	ok_fillheatmap_down(char** line, int heatmap[141][141], int i, int j, int steps, int heat)
{
	int heat2;
	static int ij;

	if (i + j > ij)
	{
		ij = i + j;
		ft_printf("D%i ij, heat %i\n", ij, heat);
	}
	if (i < 0 || i >= 141 || j < 0 || j >= 141 || heat > 1350 || (heatmap[j][i] && heatmap[j][i] <= -steps + heat + line[j][i] - '0'))
		return ;
	heat2 = heat + line[j][i] - '0';
	if (!heatmap[j][i] || heat2 <= heatmap[j][i])
	{
		heatmap[j][i] = heat2;
		if (heat2 < 1282 && j == 141 - 1 && i == 141 - 1)
			ft_printf("current solution %i\n", heat2);
	}
	// else
	// 	ft_printf("WTF\n");
	//ft_printf("processing right %i %i %c %i \n", i, j, line[j][i], heatmap[j][i]);
	ok_fillheatmap_left(line, heatmap, i - 1, j, steps, heat2);
	if (i > 0)
	{
		heat = heat2 + line[j][i - 1] - '0';
		ok_fillheatmap_left(line, heatmap, i - 2, j, steps, heat);
	}
	if (i > 1)
	{
		heat = heat2 + line[j][i - 1] - '0' + line[j][i - 2] - '0';
		ok_fillheatmap_left(line, heatmap, i - 3, j, steps, heat);
	}
	ok_fillheatmap_right(line, heatmap, i + 1, j, steps, heat2);
	if (i < 141 - 1)
	{
		heat = heat2 + line[j][i + 1] - '0';
		ok_fillheatmap_right(line, heatmap, i + 2, j, steps, heat);
	}
	if (i <  141 - 2)
	{
		heat = heat2 + line[j][i + 1] - '0' + line[j][i + 2] - '0';
		ok_fillheatmap_right(line, heatmap, i + 3, j, steps, heat);
	}
}

// void	ok_fillheatmap(char **line, int heatmap[141][141])
// {
// 	int	i;
// 	int	j;
// 	int	visited[141][141];

// 	j = 0;
// 	while (j < 141)
// 	{
// 		i = 0;
// 		while(i < 141)
// 		{
// 			visited[j][i] = 0;
// 			++i;
// 		}
// 		++j;
// 	}
// 	j = 0;
// 	visited[0][0] = 1;
// 	heatmap[0][0] = 0;
	
// }

void	ok_update(char **line, long long *ptot, int i, int j)
{
	int			heatmap[141][141];
	long long	r;
	int			steps;


	r = 0;
	j = 0;
	steps = 0;
	i = 0;
	while (j < 141)
	{
		i = 0;
		while(i < 141)
		{
			heatmap[j][i] = 0;
			++i;
		}
		++j;
	}
	while (steps < 5)
	{
		ok_fillheatmap_right(line, heatmap, 1, 0, steps, 0);
		ok_fillheatmap_right(line, heatmap, 2, 0, steps, 2);
		ok_fillheatmap_right(line, heatmap, 3, 0, steps, 5);
		ok_fillheatmap_down(line, heatmap, 0, 1, steps, 0);
		ok_fillheatmap_down(line, heatmap, 0, 2, steps, 5);
		ok_fillheatmap_down(line, heatmap, 0, 3, steps, 8);
		++steps;
		ft_printf("steps %i\n", steps);
	}
	//ok_fillheatmap(line, heatmap);
	i = 0;
	j = 0;
	while (j < 141)
	{
		i = 0;
		while(i < 141)
		{
			if (heatmap[j][i])
				r += 1;
			// if (i && j && heatmap[j][i] == heatmap[j][i - 1] + line[j][i] - '0')
			// 	ft_printf("%^*C%3i %C", 0X220022, heatmap[j][i]);
			// else
			ft_printf("%4i ", heatmap[j][i]);
			++i;
		}
		ft_printf("\n");
		++j;
	}
	(void)r;
	*ptot = heatmap[141 - 1][141 - 1];
}


// void	ok_update2(char **line, long long *ptot, int i, int j)
// {
// 	char		heatmap[141][141];
// 	long long	r;
// 	int			ii;

// 	r = 0;
// 	j = 0;
// 	i = 0;
// 	ii = 0;
// 	while (ii < 440)
// 	{
// 		r = 0;
// 		i = 0;
// 		j = 0;
// 		while (j < 141)
// 		{
// 			i = 0;
// 			while(i < 141)
// 			{
// 				heatmap[j][i] = 0;
// 				++i;
// 			}
// 			++j;
// 		}
// 		r = 0;
// 		i = 0;
// 		j = 0;
// 		while (j < 141)
// 		{
// 			i = 0;
// 			while(i < 141)
// 			{
// 				//ft_printf("%x", heatmap[j][i]);
// 				if (heatmap[j][i])
// 					r += 1;
// 				++i;
// 			}
// 			//ft_printf("\n");
// 			++j;
// 		}
// 		ft_printf("r %i\n", r);
// 		if (ii / 141 == 0)
// 		{
// 			ft_printf("processing down %i %i\n", ii / 141, ii % 141);
// 			ok_fillheatmap_down(line, heatmap, ii % 141, 0);
// 		}
// 		else if (ii / 141 == 1)
// 		{
// 			ft_printf("processing up %i %i\n", ii / 141, ii % 141);
// 			ok_fillheatmap_up(line, heatmap, ii % 141, 109);
// 		}
// 		else if (ii / 141 == 2)
// 		{
// 			ft_printf("processing right %i %i\n", ii / 141, ii % 141);
// 			ok_fillheatmap_right(line, heatmap, 0, ii % 141);
// 		}
// 		else if (ii / 141 == 3)
// 		{
// 			ft_printf("processing left %i %i\n", ii / 141, ii % 141);
// 			ok_fillheatmap_left(line, heatmap, 109, ii % 141);
// 		}
		
// 		i = 0;
// 		j = 0;
// 		r = 0;
// 		while (j < 141)
// 		{
// 			i = 0;
// 			while(i < 141)
// 			{
// 				//ft_printf("%x", heatmap[j][i]);
// 				if (heatmap[j][i])
// 					r += 1;
// 				++i;
// 			}
// 			//ft_printf("\n");
// 			++j;
// 		}
// 		ft_printf("r %i\n", r);
// 		*ptot = (r > *ptot) * r + (r <= *ptot) * *ptot;
// 		++ii;
// 	}
// }


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
	ok_update(line, &total[0], i, j);
	ft_printf("t1=%5lld\n", total[0]);
	//ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	return (0);
}
