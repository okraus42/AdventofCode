/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p16.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/16 07:18:46 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

//1 right, 2 left, 4 up, 8 down
void	ok_fillroom_left(char** line, char room[110][110], int i, int j);
void	ok_fillroom_right(char** line, char room[110][110], int i, int j);
void	ok_fillroom_up(char** line, char room[110][110], int i, int j);
void	ok_fillroom_down(char** line, char room[110][110], int i, int j);

void	ok_fillroom_right(char** line, char room[110][110], int i, int j)
{
	 if (i < 0 || i >= 110 || j < 0 || j >= 110 || room[j][i] & 1)
		return ;
	room[j][i] |= 1;
	//ft_printf("processing right %i %i %c %i \n", i, j, line[j][i], room[j][i]);
	if (line[j][i] == '|')
	{
		ok_fillroom_up(line, room, i, j - 1);
		ok_fillroom_down(line, room, i, j + 1);
	}
	else if (line[j][i] == '\\')
	{
		ok_fillroom_down(line, room, i, j + 1);
	}
	else if (line[j][i] == '/')
	{
		ok_fillroom_up(line, room, i, j - 1);
	}
	else
		ok_fillroom_right(line, room, i + 1, j);
}

void	ok_fillroom_left(char** line, char room[110][110], int i, int j)
{
	 if (i < 0 || i >= 110 || j < 0 || j >= 110 || room[j][i] & 2)
		return ;
	room[j][i] |= 2;
	//ft_printf("processing left %i %i %c %i \n", i, j, line[j][i], room[j][i]);
	if (line[j][i] == '|')
	{
		ok_fillroom_up(line, room, i, j - 1);
		ok_fillroom_down(line, room, i, j + 1);
	}
	else if (line[j][i] == '\\')
	{
		ok_fillroom_up(line, room, i, j - 1);
	}
	else if (line[j][i] == '/')
	{
		ok_fillroom_down(line, room, i, j + 1);
	}
	else
		ok_fillroom_left(line, room, i - 1, j);
}

void	ok_fillroom_up(char** line, char room[110][110], int i, int j)
{
	 if (i < 0 || i >= 110 || j < 0 || j >= 110 || room[j][i] & 4)
		return ;
	room[j][i] |= 4;
	//ft_printf("processing up %i %i %c %i \n", i, j, line[j][i], room[j][i]);
	if (line[j][i] == '-')
	{
		ok_fillroom_left(line, room, i - 1, j);
		ok_fillroom_right(line, room, i + 1, j);
	}
	else if (line[j][i] == '\\')
	{
		ok_fillroom_left(line, room, i - 1, j);
	}
	else if (line[j][i] == '/')
	{
		ok_fillroom_right(line, room, i + 1, j);
	}
	else
		ok_fillroom_up(line, room, i, j - 1);
}


void	ok_fillroom_down(char** line, char room[110][110], int i, int j)
{
	 if (i < 0 || i >= 110 || j < 0 || j >= 110 || room[j][i] & 8)
		return ;
	room[j][i] |= 8;
	//ft_printf("processing down %i %i %c %i \n", i, j, line[j][i], room[j][i]);
	if (line[j][i] == '-')
	{
		ok_fillroom_left(line, room, i - 1, j);
		ok_fillroom_right(line, room, i + 1, j);
	}
	else if (line[j][i] == '\\')
	{
		ok_fillroom_right(line, room, i + 1, j);
	}
	else if (line[j][i] == '/')
	{
		ok_fillroom_left(line, room, i - 1, j);
	}
	else
		ok_fillroom_down(line, room, i, j + 1);
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	char		room[110][110];
	long long	r;


	r = 0;
	j = 0;
	i = 0;
	while (j < 110)
	{
		i = 0;
		while(i < 110)
		{
			room[j][i] = 0;
			++i;
		}
		++j;
	}
	ok_fillroom_right(line, room, 0, 0);
	i = 0;
	j = 0;
	while (j < 110)
	{
		i = 0;
		while(i < 110)
		{
			if (room[j][i])
				r += 1;
			++i;
		}
		++j;
	}
	*ptot = (r > *ptot) * r + (r <= *ptot) * *ptot;
}


void	ok_update2(char **line, long long *ptot, int i, int j)
{
	char		room[110][110];
	long long	r;
	int			ii;

	r = 0;
	j = 0;
	i = 0;
	ii = 0;
	while (ii < 440)
	{
		r = 0;
		i = 0;
		j = 0;
		while (j < 110)
		{
			i = 0;
			while(i < 110)
			{
				room[j][i] = 0;
				++i;
			}
			++j;
		}
		r = 0;
		i = 0;
		j = 0;
		while (j < 110)
		{
			i = 0;
			while(i < 110)
			{
				//ft_printf("%x", room[j][i]);
				if (room[j][i])
					r += 1;
				++i;
			}
			//ft_printf("\n");
			++j;
		}
		ft_printf("r %i\n", r);
		if (ii / 110 == 0)
		{
			ft_printf("processing down %i %i\n", ii / 110, ii % 110);
			ok_fillroom_down(line, room, ii % 110, 0);
		}
		else if (ii / 110 == 1)
		{
			ft_printf("processing up %i %i\n", ii / 110, ii % 110);
			ok_fillroom_up(line, room, ii % 110, 109);
		}
		else if (ii / 110 == 2)
		{
			ft_printf("processing right %i %i\n", ii / 110, ii % 110);
			ok_fillroom_right(line, room, 0, ii % 110);
		}
		else if (ii / 110 == 3)
		{
			ft_printf("processing left %i %i\n", ii / 110, ii % 110);
			ok_fillroom_left(line, room, 109, ii % 110);
		}
		
		i = 0;
		j = 0;
		r = 0;
		while (j < 110)
		{
			i = 0;
			while(i < 110)
			{
				//ft_printf("%x", room[j][i]);
				if (room[j][i])
					r += 1;
				++i;
			}
			//ft_printf("\n");
			++j;
		}
		ft_printf("r %i\n", r);
		*ptot = (r > *ptot) * r + (r <= *ptot) * *ptot;
		++ii;
	}
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
	ok_update(line, &total[0], i, j);
	ft_printf("t1=%5lld\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	return (0);
}
