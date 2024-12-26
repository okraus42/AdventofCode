/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p25d.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/25 20:45:18 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define HAILS 300	//300

#define INPUT "inputtest"

#define RA 200000000000000			//7 	200000000000000
#define RB 400000000000000			//27	400000000000000

#define ABS(a) ((a > 0) * a + (a < 0) * a)
#define PN(a) ((a > 0) - (a < 0))

//16 bits step count 8 bits y, 8 bits x

typedef struct s_connection
{
	int	id1;
	int	id2;
	int	orig;
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

int	ok_karger(t_connection c[5000], int *x, int *y, int *z)
{
	int				cuts;
	int				edges;
	int				v1;
	int				v2;
	int				ee;
	int				rme;
	int				vertices;
	t_list			*v[2000];
	t_list			*tmp;
	int				*content;
	t_connection	e[5000];

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
		e[edges].orig = edges;
		++edges;
	}
	ft_printf("karger rand %i vertices %i, edges %i\n", rand() % edges, vertices, edges);
	while (vertices > 2)
	{
		//ft_printf("edges %i, vertices %i\n", edges, vertices);
		//ft_printf("e[2]i1 %i, e[2]i2 %i\n", e[2].id1, e[2].id2);
		rme = rand() % edges;
		ft_printf("rme %i e[rme]i1 %i, e[rme]i2 %i\n", rme, e[rme].id1, e[rme].id2);
		v1 = e[rme].id1;
		v2 = e[rme].id2;
		ft_lstadd_back(&v[v1], v[v2]);
		v[v2] = NULL;
		tmp = v[v1];
		while (tmp)
		{
			ee = *(int *)tmp->content;
			ft_printf("00ee %i e1 %i e2 %i\n", ee, e[ee].id1, e[ee].id2);
			if ((e[ee].id1 == v1 && e[ee].id2 == v2) || (e[ee].id1 == v2 && e[ee].id2 == v1))
			{
				if (ee == edges - 1)
				{
					ft_printf("0aee %i  e[ee]i1 %i, e[ee]i2 %i\n", ee, e[ee].id1, e[ee].id2);
					--edges;
					ft_printf("1|%i|Removing edge %i, connecting V %i and V %i\n", edges, edges, e[edges].id1, e[edges].id2);
					e[edges].id1 = 0;
					e[edges].id2 = 0;
				}
				else if (ee <= edges - 1)
				{
					--edges;
					ft_printf("3|%i|Removing edge %i, connecting V %i and V %i\n", edges, ee, e[ee].id1, e[ee].id2);
					ft_printf("v2 %i v1 %i ee %i\n", v2, v1, ee);
					ft_printf("e2 %i e1 %i edge %i\n", e[edges].id2, e[edges].id1, edges);
					while (((e[edges].id1 == v1 && e[edges].id2 == v2) || (e[edges].id1 == v2 && e[edges].id2 == v1)))
					{
						ft_printf("111e2 %i e1 %i edge %i\n", e[edges].id2, e[edges].id1, edges);
						e[edges].id1 = 0;
						e[edges].id2 = 0;
						--edges;
						ft_printf("222e2 %i e1 %i edge %i\n", e[edges].id2, e[edges].id1, edges);
					}
					if ((ee <= edges - 1))
					{
						e[ee].id1 = e[edges].id1;
						e[ee].id2 = e[edges].id2;
						e[ee].orig = e[edges].orig;
						if (e[ee].id2 == v2)
							e[ee].id2 = v1;
						else if (e[ee].id1 == v2)
							e[ee].id1 = v1;
					}
					ft_printf("e2 %i e1 %i ee %i\n", e[ee].id2, e[ee].id1, ee);
					ft_printf("ee2 %i || %i %i ||orig %i\n", ee, e[ee].id1, e[ee].id2, e[ee].orig);
					ft_printf("0bee %i  e[edge]i1 %i, e[edge]i2 %i\n", ee, e[edges].id1, e[edges].id2);
					
					e[edges].id1 = 0;
					e[edges].id2 = 0;
				}
				ft_printf("0ee %i  v1 %i, v2 %i\n", ee, v1, v2);
			}
			//ft_printf("2ee %i  e[ee]i1 %i, e[ee]i2 %i\n", ee, e[ee].id1, e[ee].id2);
			else if(e[ee].id2 == v2 && (e[ee].id2 || e[ee].id1))
			{
				ft_printf("eav2 %i v1 %i ee %i\n", v2, v1, ee);
				e[ee].id2 = v1;
				ft_printf("eae2 %i e1 %i ee %i\n", e[ee].id2, e[ee].id1, ee);
			}
			//ft_printf("3ee %i  e[ee]i1 %i, e[ee]i2 %i\n", ee, e[ee].id1, e[ee].id2);
			else if (e[ee].id1 == v2 && (e[ee].id2 || e[ee].id1))
			{
				ft_printf("ebv2 %i v1 %i ee %i\n", v2, v1, ee);
				e[ee].id1 = v1;
				ft_printf("ebe2 %i e1 %i ee %i\n", e[ee].id2, e[ee].id1, ee);
			}
			ft_printf("4ee %i  e[ee]i1 %i, e[ee]i2 %i\n", ee, e[ee].id1, e[ee].id2);
			tmp = tmp->next;
		}
		//ft_printf("rme %i e[rme]i1 %i, e[rme]i2 %i\n", rme, e[rme].id1, e[rme].id2);
		// for (int m = 0; m < 1; ++m)
		// 	ft_printf("orig %i %i\n", m, e[m].orig);
		// for (int i = 0; i < 15; ++i)
		// 	if(v[i])
		// 	{
		// 		ft_printf("VVV %i \n", i);
		// 		tmp = v[i];
		// 		while (tmp)
		// 		{
		// 			ft_printf("%i\n", *(int *)tmp->content);
		// 			tmp = tmp->next;
		// 		}
		// 	}
		// for (int j = 0; j < 33; ++j)
		// 	ft_printf("EEE %i %i old %i\n", e[j].id1, e[j].id2, e[j].orig);
		--vertices;
	}
	for (int m = 0; m < 15; ++m)
	{
		ft_printf("%i %i %i %i orig %i %i\n", m, e[m].id1, e[m].id2, e[m].orig, c[e[m].orig].id1, c[e[m].orig].id2);
	}
	//ft_printf("edges %i, vertices %i\n", edges, vertices);
	//ft_printf("e[0]i1 %i, e[0]i2 %i\n", e[0].id1, e[0].id2);
	cuts = 0;
	while (e[cuts].id1 || e[cuts].id2)
	{
		ft_printf("e[cuts]i1 %i, e[cuts]i2 %i\n", e[cuts].id1, e[cuts].id2);
		++cuts;
	}
	//ft_printf("e[cuts]i1 %i, e[cuts]i2 %i\n", e[cuts].id1, e[cuts].id2);
	if (cuts <= 3)
	{
		*x = e[0].orig;
		*y = e[1].orig;
		*z = e[2].orig;
		ft_printf("orig %i orig %i orig %i\n", e[0].orig, e[1].orig, e[2].orig);
	}
	ft_lstclear(&v[e[0].id1], free);
	ft_lstclear(&v[e[0].id2], free);
	v[e[0].id1] = NULL;
	v[e[0].id2] = NULL;
	vertices = 0;
	while (vertices < 2000)
	{
		if (v[vertices])
		{
			ft_printf("not free %i\n", vertices);
			ft_lstclear(&v[vertices], free);
		}
		v[vertices] = NULL;
		++vertices;
	}
	ft_printf("Cuts %i\n", cuts);
	return (cuts);
}

long long	ok_magic(char dict[2000][4], t_connection c[5000])
{
	long long	r;
	long long	d;
	int			x;
	int			y;
	int			z;
	int			cuts;

	d = 0;
	while (dict[d][0])
		++d;
	r = 0;
	z = 0;
	y = 0;
	x = 0;
	ft_printf("magic\n");
	cuts = 5;
	while (cuts > 3)
	{
		cuts = ok_karger(c, &x, &y, &z);
	}
	ft_printf("%i %i %i\n", z, y, x);
	r = ok_maths(c, z, y, x);
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
	srand(0x1bbfc6ab);
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