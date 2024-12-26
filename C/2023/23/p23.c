/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p23.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/23 15:49:14 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define WIDTH 10
#define LENGTH 10
#define HEIGHT 400

#define INPUT "inputtest"

#define ABS(a) ((a > 0) * a + (a < 0) * a)
#define PN(a) ((a > 0) - (a < 0))

t_list		*head[4096];
int			g_count;
//16 bits step count 8 bits y, 8 bits x

void	ok_lstcopy(t_list **oldhead, t_list	**newhead)
{
	t_list			*new;
	t_list			*tmp;
	unsigned int	*content;

	if (*oldhead == NULL)
	{
		*newhead = NULL;
		return ;
	}
	tmp = *oldhead;
	while (tmp)
	{
		content = malloc(sizeof(unsigned int));
		*content = *(unsigned int *)tmp->content;
		new = ft_lstnew(content);
		ft_lstadd_back(newhead, new);
		tmp = tmp->next;
	}
}

int	ok_visited(t_list **head, int pos)
{
	t_list 			*tmp;
	unsigned int	u;
	int				oldpos;

	tmp = *head;
	while (tmp)
	{
		u = *(unsigned int *)tmp->content;
		oldpos = u & 0xFFFF;
		//ft_printf("pos %4x, oldpos %4x\n", pos, oldpos);
		if (pos == oldpos)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ok_filllists(char **map, t_list *head[4096], int pos, int lc)
{
	unsigned int	*info;
	t_list			*new;
	t_list			*old;
	// t_list			*old2;
	// t_list			*old3;
	int				y;
	int				x;
	int				oldpos;

	y = (pos & 0xFF00) >> 8;
	x = (pos & 0xFF);
	old = NULL;
	// old2 = NULL;
	// old3 = NULL;
	info = malloc(sizeof(unsigned int));
	if (!head[lc])
	{
		*info = pos;
		oldpos = 0;
	}
	else
	{
		*info = (*(unsigned int *)(head[lc]->content) & 0xFFFF0000 )+ 0x10000;
		*info |= pos;
		oldpos = *(unsigned int *)(head[lc]->content) & 0xFFFF;
		if (ok_visited(&head[lc], pos))
		{
			//ft_printf("VISITED\n");
			return ;
		}
	}
	//ft_printf("info %8x, pos %4x oldpos %4x, steps %5i, pos %3i %3i, lc %i\n", *info, pos, oldpos, *info >> 16,((pos & 0xFF00) >> 8), pos & 0xFF, lc);
	new = ft_lstnew(info);
	ft_lstadd_front(&head[lc], new);
	if ((map[y + 1][x] == '.' || map[y + 1][x] == 'v') && (oldpos != pos + 256))
	{
		old = head[lc];
		ok_filllists(map, head, pos + 256, lc);
	}
	if ((map[y - 1][x] == '.' || map[y - 1][x] == '^') && (oldpos != pos - 256))
	{
		if (old)
		{
			++g_count;
			//ft_printf("UP lc %i, g_count %i\n", lc, g_count);
			ok_lstcopy(&old, &head[g_count]);
			ok_filllists(map, head, pos - 256, g_count);
		}
		else
		{
			old = head[lc];
			ok_filllists(map, head, pos - 256, lc);
		}
	}
	if ((map[y][x + 1] == '.' || map[y][x + 1] == '>') && (oldpos != pos + 1))
	{
		if (old)
		{
			++g_count;
			//ft_printf("RIGHT lc %i, g_count %i\n", lc, g_count);
			ok_lstcopy(&old, &head[g_count]);
			ok_filllists(map, head, pos + 1, g_count);
		}
		else
		{
			old = head[lc];
			ok_filllists(map, head, pos + 1, lc);
		}
	}
	if ((map[y][x - 1] == '.' || map[y][x - 1] == '<') && (oldpos != pos - 1))
	{
		if (old)
		{
			++g_count;
			//ft_printf("LEFT lc %i, g_count %i\n", lc, g_count);
			ok_lstcopy(&old, &head[g_count]);
			ok_filllists(map, head, pos - 1, g_count);
		}
		else
		{
			ok_filllists(map, head, pos - 1, lc);
		}
	}
	if (map[y + 1][x] == 'E')
	{
		info = malloc(sizeof(unsigned int));
		*info = *(unsigned int *)(head[lc]->content) & 0xFFFF0000 + 0x10000;
		*info |= pos + 256;
		new = ft_lstnew(info);
		ft_lstadd_front(&head[lc], new);
	}
}

void	ok_path(char **m, t_list *lst)
{
	int	y;
	int	x;
	int	steps;

	while (lst)
	{
		y = ((*(unsigned int *)lst->content) &0xFF00) >> 8;
		x = (*(unsigned int *)lst->content) &0xFF;
		steps = ((*(unsigned int *)lst->content) & 0xFFFF0000) >> 16;
		m[y][x] = 'O';
		ft_printf("steps %6i, y %3i, x %3i\n", steps, y, x);
		lst = lst->next;
	}
}

long long	ok_process(t_list *head[4096], char **map)
{
	int				i;
	long long		r;
	long long		t;
	char			**map2;

	i = 0;
	r = 0;
	while (head[i])
	{
		t = ft_lstsize(head[i]);
		ft_printf("t = %lli\n", t);
		ft_printf("y = %i\n", (*(unsigned int *)head[i]->content % 0xFF00) >> 8 );
		if (r < t)
			r = t;
		//ft_printf("%i\n", ft_lstsize(head[i]));
		map2 = ft_copy_split(map);
		ok_path(map2, head[i]);
		ft_put_split(map2);
		++i;
	}
	ft_printf("LISTS %i \n", i);
	(void)map;
	return (r);
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	long long	r;
	int			startx;
	int			starty;
	t_list		*head[4096];

	j = 0;
	i = 0;
	while(line[j][i] != '.')
		i++;
	line[j][i] = 'S';
	startx = i;
	starty = 1;
	while(line[j] && line[j + 1])
		++j;
	i = 0;
	while(line[j][i] != '.')
		i++;
	line[j][i] = 'E';
	ok_filllists(line, head, starty << 8 | startx, 0);
	r = ok_process(head, line);
	*ptot = r;
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	long long	r;
	int			startx;
	int			starty;
	t_list		*head[4096];

	j = 0;
	i = 0;
	while(line[j][i] != 'S')
		i++;
	line[j][i] = 'S';
	startx = i;
	starty = 1;
	while(line[j] && line[j + 1])
		++j;
	i = 0;
	while(line[j][i] != 'E')
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
	ok_filllists(line, head, starty << 8 | startx, 0);
	r = ok_process(head, line);
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
