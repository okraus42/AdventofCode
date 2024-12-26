/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p25.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/26 11:12:27 by okraus           ###   ########.fr       */
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
}	t_connection;

typedef struct s_component
{
	int				id;
	t_connection	connections[10];
	
}	t_component;

void	ok_wordtodict(char dict[10000][4], char word[4])
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
	z = 0;//226 next time
	ft_printf("magic\n");
	while (c[z].id1 || c[z].id2)
	{
		y = z + 1;
		ft_printf("Processing...%i\n", z);
		while (c[y].id1 || c[y].id2)
		{
			ft_printf("Processing...%i %i\n", z, y);
			x = y + 1;
			while (c[x].id1 || c[x].id2)
			{
				r = ok_maths(c, z, y, x);
				if (r != d)
					return (r * (d - r));
				++x;
			}
			++y;
		}
		++z;
	}
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

//0-225 bruteforced in 27 hours