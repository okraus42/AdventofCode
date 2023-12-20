/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p20.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/20 07:53:27 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define LOW 1
#define HIGH 2
#define SIGNAL 3

typedef struct s_ff
{
	char	name[4];
	int		state;
	int		signal;
	char	**targets;
}	t_ff;

typedef struct s_con
{
	char	name[4];
	char	**source;
	int		received[50];
	int		signal;
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

void	ok_createff(t_ff *ff, char *str)
{
	int	i;

	i = 1;
	while (str[i] != ' ')
	{
		ff->name[i - 1] = str[i];
		++i;
	}
	while (str[i])
	{
		if (str[i] == ' ');
			str[i] = ',';
		++i;
	}
	i = 0;
	while (str[i] != '>')
	{
		++i;
	}
	ff->state = 0;
	ff->signal = 0;
	ff->targets = ft_split(&str[i + 1], ',');
}

void	ok_createcon(t_con *con, char *str)
{
	int	i;

	i = 1;
	while (str[i] != ' ')
	{
		con->name[i - 1] = str[i];
		++i;
	}
	while (str[i])
	{
		if (str[i] == ' ');
			str[i] = ',';
		++i;
	}
	i = 0;
	while (str[i] != '>')
	{
		++i;
	}
	con->signal = 0;
	con->targets = ft_split(&str[i + 1], ',');
}

void	ok_createbroad(t_broadcast *broad, char *str)
{
	int	i;

	while (str[i])
	{
		if (str[i] == ' ');
			str[i] = ',';
		++i;
	}
	i = 0;
	while (str[i] != '>')
	{
		++i;
	}
	broad->signal = 0;
	broad->targets = ft_split(&str[i + 1], ',');
}

void	ok_updatecon(t_ff ff[50], t_con con[50], int f, int c)
{
	int	i;
	int	j;
	int	s;
	int d;

	d = 0;
	while (d < c)
	{
		i = 0;
		s = 0;
		while (i < c)
		{
			while (con[i].targets[j])
			{
				if (!ft_strchr(con[i].targets[j], con[d].name))
					++s;
				++j;
			}
			++i;
		}
		i = 0;
		while (i < f)
		{
			while (ff[i].targets[j])
			{
				if (!ft_strchr(ff[i].targets[j], con[d].name))
					++s;
				++j;
			}
			++i;
		}
		con[d].source = malloc(sizeof(char *) * (s + 1));
		i = 0;
		s = 0;
		while (i < c)
		{
			while (con[i].targets[j])
			{
				if (!ft_strchr(con[i].targets[j], con[d].name))
				{
					con[d].source[s] = ft_stringcopy(con[i].name);
					++s;
				}
				++j;
			}
			++i;
		}
		i = 0;
		while (i < f)
		{
			while (ff[i].targets[j])
			{
				if (!ft_strchr(ff[i].targets[j], con[d].name))
				{
					con[d].source[s] = ft_stringcopy(ff[i].name);
					++s;
				}
				++j;
			}
			++i;
		}
		con[d].source[s] = NULL;
		++d;
	}
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	t_ff		ff[50];
	t_con		con[10];
	t_broadcast	broad;
	long long	r;
	int			f;
	int			c;

	j = 0;
	r = 0;
	f = 0;
	c = 0;
	i = 0;
	while (line[j])
	{
		if (line[j][0] == '%')
		{
			ok_createff(&ff[f], line[j]);
			++f;
		}
		else if (line[j][0] == '&')
		{
			ok_createcon(&con[c], line[j]);
			++c;
		}
		else
		{
			ok_createff(&broad, line[j]);
		}
		++j;
	}
	ok_updatecon(ff, con, f, c);
	//update con
	//run signals
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
	ok_update(line, &total[0], i, j);
	ft_printf("t1=%5lld\n", total[0]);
	//ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	return (0);
}
