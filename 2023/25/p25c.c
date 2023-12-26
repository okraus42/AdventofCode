/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p25c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/26 07:09:45 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define HAILS 300	//300

#define INPUT "input"

#define RA 200000000000000			//7 	200000000000000
#define RB 400000000000000			//27	400000000000000

#define ABS(a) ((a > 0) * a + (a < 0) * a)
#define PN(a) ((a > 0) - (a < 0))

//16 bits step count 8 bits y, 8 bits x

typedef struct s_connection
{
	int	id1;
	int	id2;
	int	usage;
}	t_connection;

typedef struct s_vertex
{
	int		id;
	t_list	*edges;
	
}	t_vertex;

void	ok_wordtodict(char dict[2000][4], char word[4])
{
	int	d;

	d = 0;
	while (dict[d][0])
	{
		if (dict[d][0] == word[0] && dict[d][1] == word[1] && dict[d][2] == word[2])
			return ;
		++d;
	}
	dict[d][0] = word[0];
	dict[d][1] = word[1];
	dict[d][2] = word[2];
}

void	ok_filldict(char **line, char dictionary[2000][4])
{
	char	word[4];
	int		w;
	int		j;
	int		d;
	int		i;

	d = 0;
	while (d < 2000)
	{
		dictionary[d][0] = 0;
		dictionary[d][1] = 0;
		dictionary[d][2] = 0;
		dictionary[d][3] = 0;
		++d;
	}
	d = 0;
	j = 0;
	while (line[j])
	{
		w = 0;
		i = 0;
		while (line[j][i])
		{
			if (ft_isalpha(line[j][i]))
			{
				word[w] = line[j][i];
				++w;
			}
			if (w == 3)
			{
				word[w] = 0;
				ok_wordtodict(dictionary, word);
				w = 0;
			}
			++i;
		}
		++j;
	}
}

int	ok_wordid(char dict[10000][4], char *word)
{
	int	d;

	d = 0;
	while (dict[d][0])
	{
		if (dict[d][0] == word[0] && dict[d][1] == word[1] && dict[d][2] == word[2])
			return (d);
		++d;
	}
	return (-1);
}

void	ok_fillconn(char **line, char dict[2000][4], t_connection c[5000])
{
	int		j;
	int		i;
	int		k;
	int		w;

	k = 0;
	while (k < 5000)
	{
		c[k].id1 = 0;
		c[k].id2 = 0;
		++k;
	}
	k = 0;
	j = 0;
	while (line[j])
	{
		w = 0;
		i = 4;
		while (line[j][i])
		{
			if (ft_isalpha(line[j][i]))
			{
				++w;
			}
			if (w == 3)
			{
				c[k].id1 = ok_wordid(dict, line[j]);
				c[k].id2 = ok_wordid(dict, &line[j][i - 2]);
				++k;
				w = 0;
			}
			++i;
		}
		++j;
	}
}

long long	ok_maths(t_connection c[5000], int z, int y, int x)
{
	long long	r;
	int			i;
	int			d;
	int			found[2000];

	i = 0;
	while (i < 2000)
	{
		found[i] = 0;
		++i;
	}
	i = 0;
	if (i == x || i == y || i == z)
		++i;
	found[c[i].id1] = 1;
	found[c[i].id2] = 1;
	d = 1;
	while (d)
	{
		i = 0;
		d = 0;
		while (c[i].id1 || c[i].id2)
		{
			if (i == x || i == y || i == z)
			{
				++i;
				continue ;
			}
			if (!found[c[i].id1] && found[c[i].id2])
			{
				found[c[i].id1] = 1;
				d = 1;
			}
			else if(found[c[i].id1] && !found[c[i].id2])
			{
				found[c[i].id2] = 1;
				d = 1;
			}
			++i;
		}
	}
	i = 0;
	r = 0;
	while (i < 2000)
	{
		if (found[i])
			++r;
		++i;
	}
	return (r);
}

void	ok_traverse(t_connection e[5000], t_list *v[2000], int ee, int vv, int pp, int step, int f[5000], int path[4][2000])
{
	t_list	*tmp;
	int		v2;
	int		e2;

	if (f[ee])
		return ;
	if (e[ee].id1 == vv)
		v2 = e[ee].id2;
	else
		v2 = e[ee].id1;
	//ft_printf("ee = %i, vv = %i, v2 = %i\n", ee, vv, v2);
	//ft_printf("ee = %i, vv = %i, step = %i\n", ee, vv, step);
	if (path[pp][v2] > step)
		path[pp][v2] = step;
	else
		return ;
	++step;
	tmp = v[v2];
	while (tmp)
	{
		e2 = *(int *)tmp->content;
		//ft_printf("Traversing ee %3i, vv %3i, pp %3i, step %3i\n", e2, v2, pp, step);
		ok_traverse(e, v, e2, v2, pp, step, f, path);
		tmp = tmp->next;
	}
}

void	ok_block_path(t_connection e[5000], t_list *v[2000], int vstart, int vend, int pp, int f[5000], int path[4][2000])
{
	t_list	*tmp;
	int		vv;
	int		v1;
	int		v2;
	int		step;

	vv = vend;
	while (vv != vstart)
	{
		step = path[pp][vv];
		tmp = v[vv];
		//ft_printf("vv %i, step = %i\n", vv, step);
		while (1)
		{
			if (f[*(int *)tmp->content])
			{
				tmp = tmp->next;
				continue ;
			}
			v1 = e[*(int *)tmp->content].id1;
			v2 = e[*(int *)tmp->content].id2;
			if (step > path[pp][v1])
			{
				f[*(int *)tmp->content] = 1;
				step = path[pp][v1];
				vv = v1;
				break ;
			}
			if (step > path[pp][v2])
			{
				f[*(int *)tmp->content] = 1;
				step = path[pp][v2];
				vv = v2;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

int	ok_solver(t_connection c[5000], int *x, int *y, int *z)
{
	int				edges;
	int				vertices;
	t_list			*v[2000];
	t_list			*tmp;
	int				*content;
	t_connection	e[5000];
	int				group[2000];
	int				f[5000];
	int				path[4][2000];
	int				i;
	int				ee;
	int				d;

	vertices = 0;
	while (vertices < 2000)
	{
		v[vertices] = NULL;
		++vertices;
	}
	//fill vertices and count them and count edges
	edges = 0;
	vertices = 0;
	while (c[edges].id1 || c[edges].id2)
	{
		e[edges].id1 = c[edges].id1;
		e[edges].id2 = c[edges].id2;
		if (e[edges].id1 >= vertices)
			vertices = e[edges].id1 + 1;
		if (e[edges].id2 >= vertices)
			vertices = e[edges].id2 + 1;
		content = malloc(sizeof(int));
		*content = edges;
		tmp = ft_lstnew(content);
		ft_lstadd_front(&v[e[edges].id1], tmp);
		content = malloc(sizeof(int));
		*content = edges;
		tmp = ft_lstnew(content);
		ft_lstadd_front(&v[e[edges].id2], tmp);
		++edges;
	}
	i = 0;
	while (i < 2000)
	{
		group[i] = 0;
		f[i] = 0;
		path[0][i] = 0xffff;
		path[1][i] = 0xffff;
		path[2][i] = 0xffff;
		path[3][i] = 0xffff;
		++i;
	}
	while (i < 5000)
	{
		f[i] = 0;
		++i;
	}
	i = 0;
	path[0][i] = 0;
	path[1][i] = 0;
	path[2][i] = 0;
	path[3][i] = 0;
	//vertices I cannot get to in 4 paths are group 2, other vertices are group 1
	// init groups
	i = 0;
	while (i < 15)
	{
		//ft_printf("VERTEX i %i  VERTEX\n", i);
		tmp = v[i];
		while (tmp)
		{
			//ft_printf("   edge %i  v1 %i v2 %i,\n", *(int *)tmp->content, e[*(int *)tmp->content].id1, e[*(int *)tmp->content].id2);
			tmp = tmp->next;
		}
		++i;
	}
	tmp = v[0];
	while (tmp)
	{
		ee = *(int *)tmp->content;
		//ft_printf("Traversing ee %3i, vv %3i, pp %3i, step %3i\n", ee, 0, 0, 1);
		ok_traverse(e, v, ee, 0, 0, 1, f, path);
		tmp = tmp->next;
	}
	i = 0;
	while (i < 30)
	{
		//ft_printf("%2i path i %i, f %i\n",i,  path[0][i], f[i]);
		++i;
	}
	//ft_printf("blocking path\n");
	ok_block_path(e, v, 0, 25, 0, f, path);
	tmp = v[0];
	while (tmp)
	{
		ee = *(int *)tmp->content;
		//ft_printf("Traversing 1 ee %3i, vv %3i, pp %3i, step %3i\n", ee, 0, 0, 1);
		ok_traverse(e, v, ee, 0, 1, 1, f, path);
		tmp = tmp->next;
	}
	i = 0;
	while (i < 30)
	{
		//ft_printf("%2i path i %i, f %i\n",i,  path[0][i], f[i]);
		++i;
	}
	//ft_printf("blocking path 1 \n");
	ok_block_path(e, v, 0, 25, 1, f, path);
	tmp = v[0];
	while (tmp)
	{
		ee = *(int *)tmp->content;
		//ft_printf("Traversing 2 ee %3i, vv %3i, pp %3i, step %3i\n", ee, 0, 0, 1);
		ok_traverse(e, v, ee, 0, 2, 1, f, path);
		tmp = tmp->next;
	}
	i = 0;
	while (i < 30)
	{
		//ft_printf("%2i path i %i, f %i\n",i,  path[0][i], f[i]);
		++i;
	}
	//ft_printf("blocking path 2\n");
	ok_block_path(e, v, 0, 25, 2, f, path);
	i = 0;
	while (i < 35)
	{
		//ft_printf("%2i, path i %i, f %i\n",i,  path[0][i], f[i]);
		++i;
	}
	//find three edges that connect verteces fropm group 1 and group 2
	*x = 0;
	*y = 1;
	*z = 2;
	group[0] = 1;
	d = 1;
	while (d)
	{
		i = 0;
		d = 0;
		while (c[i].id1 || c[i].id2)
		{
			//ft_printf("Final countdown %i\n", i);
			if (f[i])
			{
				++i;
				continue ;
			}
			if (!group[c[i].id1] && group[c[i].id2])
			{
				group[c[i].id1] = 1;
				d = 1;
			}
			else if(group[c[i].id1] && !group[c[i].id2])
			{
				group[c[i].id2] = 1;
				d = 1;
			}
			++i;
		}
	}
	i = 0;
	long long r = 0;
	while (i < 2000)
	{
		if (group[i])
			++r;
		++i;
	}
	return (r);
}

long long	ok_magic(char dict[2000][4], t_connection c[5000])
{
	long long	r;
	long long	d;
	int			x;
	int			y;
	int			z;

	d = 0;
	while (dict[d][0])
		++d;
	r = 0;
	z = 0;
	y = 0;
	x = 0;
	ft_printf("magic\n");
	ft_printf("%i %i %i\n", z, y, x);
	r = ok_solver(c, &x, &y, &z);
	if (r != d)
		return (r * (d - r));
	return (r);
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	long long		r;
	char			dictionary[2000][4];
	t_connection	c[5000];


	j = 0;
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			if (line[j][i] == ':')
				line[j][i] = ' ';
			++i;
		}
		++j;
	}
	ok_filldict(line, dictionary);
	ok_fillconn(line, dictionary, c);
	j = 0;
	while (dictionary[j][0])
	{
		ft_printf("%4i: %s\n", j, dictionary[j]);
		++j;
	}
	j = 0;
	while (c[j].id1 || c[j].id2)
	{
		ft_printf("connection %5i >> %4i: %4i\n",j, c[j].id1, c[j].id2);
		++j;
	}
	ft_printf("magic?\n");
	r = ok_magic(dictionary, c);
	//r = 0;
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

/// https://www.scaler.com/topics/data-structures/kargers-algorithm-for-minimum-cut/
// instead of brute force