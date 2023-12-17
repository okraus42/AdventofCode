/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p17b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/17 07:39:25 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

//1 right, 2 left, 4 up, 8 down
void	ok_fillheatmap2_left(char** line, int heatmap[141][141], int i, int j, int steps, int heat);
void	ok_fillheatmap2_right(char** line, int heatmap[141][141], int i, int j, int steps, int heat);
void	ok_fillheatmap2_up(char** line, int heatmap[141][141], int i, int j, int steps, int heat);
void	ok_fillheatmap2_down(char** line, int heatmap[141][141], int i, int j, int steps, int heat);

void	ok_fillheatmap2_right(char** line, int heatmap[141][141], int i, int j, int steps, int heat)
{
	if (i < 0 || i >= 141 || j < 0 || j >= 141 || (heatmap[j][i] && heatmap[j][i] <= heat + line[j][i] - '0'))
		return ;
	heatmap[j][i] = heat + line[j][i] - '0';
	++steps;
	//ft_printf("processing right %i %i %c %i \n", i, j, line[j][i], heatmap[j][i]);
	if (steps >= 4)
	{
		ok_fillheatmap2_up(line, heatmap, i, j - 1, 0, heatmap[j][i]);
		ok_fillheatmap2_down(line, heatmap, i, j + 1, 0, heatmap[j][i]);
	}
	ok_fillheatmap2_right(line, heatmap, i + 1, j, steps, heatmap[j][i]);
}

void	ok_fillheatmap2_left(char** line, int heatmap[141][141], int i, int j, int steps, int heat)
{
	if (i < 0 || i >= 141 || j < 0 || j >= 141 || (heatmap[j][i] && heatmap[j][i] <= heat + line[j][i] - '0'))
		return ;
	heatmap[j][i] = heat + line[j][i] - '0';
	++steps;
	//ft_printf("processing right %i %i %c %i \n", i, j, line[j][i], heatmap[j][i]);
	if (steps >= 4)
	{
		ok_fillheatmap2_up(line, heatmap, i, j - 1, 0, heatmap[j][i]);
		ok_fillheatmap2_down(line, heatmap, i, j + 1, 0, heatmap[j][i]);
	}
	ok_fillheatmap2_left(line, heatmap, i - 1, j, steps, heatmap[j][i]);
}

void	ok_fillheatmap2_up(char** line, int heatmap[141][141], int i, int j, int steps, int heat)
{
	if (i < 0 || i >= 141 || j < 0 || j >= 141 || (heatmap[j][i] && heatmap[j][i] <= heat + line[j][i] - '0'))
		return ;
	heatmap[j][i] = heat + line[j][i] - '0';
	++steps;
	//ft_printf("processing right %i %i %c %i \n", i, j, line[j][i], heatmap[j][i]);
	if (steps >= 4)
	{
		ok_fillheatmap2_left(line, heatmap, i - 1, j, 0, heatmap[j][i]);
		ok_fillheatmap2_right(line, heatmap, i + 1, j, 0, heatmap[j][i]);
	}
	ok_fillheatmap2_up(line, heatmap, i, j - 1, steps, heatmap[j][i]);
}


void	ok_fillheatmap2_down(char** line, int heatmap[141][141], int i, int j, int steps, int heat)
{
	if (i < 0 || i >= 141 || j < 0 || j >= 141 || (heatmap[j][i] && heatmap[j][i] <= heat + line[j][i] - '0'))
		return ;
	heatmap[j][i] = heat + line[j][i] - '0';
	++steps;
	//ft_printf("processing right %i %i %c %i \n", i, j, line[j][i], heatmap[j][i]);
	if (steps >= 4)
	{
		ok_fillheatmap2_left(line, heatmap, i - 1, j, 0, heatmap[j][i]);
		ok_fillheatmap2_right(line, heatmap, i + 1, j, 0, heatmap[j][i]);
	}
	ok_fillheatmap2_down(line, heatmap, i, j + 1, steps, heatmap[j][i]);
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	int		heatmap[141][141];
	long long	r;


	r = 0;
	j = 0;
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
	ok_fillheatmap2_right(line, heatmap, 1, 0, 0, 0);
	ok_fillheatmap2_down(line, heatmap, 0, 1, 0, 0);
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
			//ft_printf("%4i ", heatmap[j][i]);
			++i;
		}
		//ft_printf("\n");
		++j;
	}
	(void)r;
	*ptot = heatmap[140][140];
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
// 			ok_fillheatmap2_down(line, heatmap, ii % 141, 0);
// 		}
// 		else if (ii / 141 == 1)
// 		{
// 			ft_printf("processing up %i %i\n", ii / 141, ii % 141);
// 			ok_fillheatmap2_up(line, heatmap, ii % 141, 109);
// 		}
// 		else if (ii / 141 == 2)
// 		{
// 			ft_printf("processing right %i %i\n", ii / 141, ii % 141);
// 			ok_fillheatmap2_right(line, heatmap, 0, ii % 141);
// 		}
// 		else if (ii / 141 == 3)
// 		{
// 			ft_printf("processing left %i %i\n", ii / 141, ii % 141);
// 			ok_fillheatmap2_left(line, heatmap, 109, ii % 141);
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
	//ok_update(line, &total[0], i, j);
	ft_printf("t1=%5lld\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	return (0);
}
