/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p20.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/21 10:30:35 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define LOW 1
#define HIGH 2
#define SIGNAL 3
#define RUNS 1000

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
	int		signal[50];
	int		iter[50];
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
	ff->name[i - 1] = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = ',';
		++i;
	}
	i = 0;
	while (str[i] != '>')
	{
		++i;
	}
	ff->iter = 0;
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
	con->name[i - 1] = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = ',';
		++i;
	}
	i = 0;
	while (str[i] != '>')
	{
		++i;
	}
	con->targets = ft_split(&str[i + 1], ',');
}

void	ok_createbroad(t_broadcast *broad, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
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
			j = 0;
			while (con[i].targets[j])
			{
				if (!ft_strncmp(con[i].targets[j], con[d].name, 3))
					++s;
				++j;
			}
			++i;
		}
		i = 0;
		while (i < f)
		{
			j = 0;
			while (ff[i].targets[j])
			{
				if (!ft_strncmp(ff[i].targets[j], con[d].name, 3))
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
			j = 0;
			while (con[i].targets[j])
			{
				if (!ft_strncmp(con[i].targets[j], con[d].name, 3))
				{
					con[d].source[s] = ft_stringcopy(con[i].name);
					con[d].received[s] = LOW;
					con[d].signal[s] = 0;
					con[d].iter[s] = 0;
					//ft_printf("??? s %i d %i i %i j %i name %s source %s iter %i\n", s, d, i, j, con[d].name, con[d].source[s], con[d].iter[s]);
					++s;
				}
				++j;
			}
			++i;
		}
		i = 0;
		while (i < f)
		{
			j = 0;
			while (ff[i].targets[j])
			{
				if (!ft_strncmp(ff[i].targets[j], con[d].name, 3))
				{
					con[d].source[s] = ft_stringcopy(ff[i].name);
					con[d].received[s] = LOW;
					con[d].signal[s] = 0;
					con[d].iter[s] = 0;
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

// typedef struct s_signal
// {
// 	char	from[4];
// 	char	to[4];
// 	int		signal;
// }	t_signal;

void	ok_createsignal(t_list **head, char *target, char *source, int signal)
{
	t_list		*new;
	t_signal	*sig;

	sig = malloc(sizeof(t_signal));
	if (source)
	{
		sig->from[0] = source[0];
		sig->from[1] = source[1];
		sig->from[2] = source[2];
		sig->from[3] = 0;
	}
	else
	sig->from[0] = 0;
	sig->to[0] = target[0];
	sig->to[1] = target[1];
	sig->to[2] = target[2];
	sig->to[3] = 0;
	sig->signal = signal;
	new = ft_lstnew(sig);
	ft_lstadd_back(head, new);
}

void	ok_execff(t_signal *sig, t_ff *ff, int *iter)
{
	if (sig->signal & LOW)
	{
		ff->state ^= 1;
		ff->signal = LOW;
		ff->iter = *iter;
	}
}

void	ok_execcon(t_signal *sig, t_con *con, int *iter)
{
	int	i;

	i = 0;
	while (con->source[i])
	{
		if (!ft_strncmp(sig->from, con->source[i], 3))
		{
			con->iter[i] = *iter;
			con->received[i] = sig->signal;
			con->signal[i] = sig->signal;
		}
		++i;
	}
}

void	ok_executesig(t_signal *sig, t_ff ff[50], t_con con[50], int *iter)
{
	int	i;

	i = 0;
	while (ff[i].name[0])
	{
		if (!ft_strncmp(sig->to, ff[i].name, 3))
		{
			ok_execff(sig, &ff[i], iter);
			return ;
		}
		++i;
	}
	i = 0;
	while (con[i].name[0])
	{
		if (!ft_strncmp(sig->to, con[i].name, 3))
		{
			ok_execcon(sig, &con[i], iter);
			return ;
		}
		++i;
	}
	ft_printf("%^*CFailed to execute signal from %s to %s%C\n", 0x880000, sig->from, sig->to);
}

void	ok_ffsig(t_list **head, t_ff *ff)
{
	int	i;

	i = 0;
	if (ff->state)
	{
		while (ff->targets[i])
		{
			ok_createsignal(head, ff->targets[i], ff->name, HIGH);
			++i;
		}
	}
	else
	{
		while (ff->targets[i])
		{
			ok_createsignal(head, ff->targets[i], ff->name, LOW);
			++i;
		}
	}
}

void	ok_consig(t_list **head, t_con *con)
{
	int	i;
	int	sig;

	i = 0;
	sig = LOW;
	while (con->source[i])
	{
		if (con->received[i] == LOW)
			sig = HIGH;
		ft_printf("con %s, source %s, val %i sig %i\n", con->name, con->source[i], con->received[i], sig);
		++i;
	}
	i = 0;
	while (con->targets[i])
	{
		//ft_printf("sig2 %i\n", sig);
		ok_createsignal(head, con->targets[i], con->name, sig);
		++i;
	}
}

void	ok_createlist(t_list **head, t_ff ff[50], t_con con[50], int *iter)
{
	int i;
	int	j;

	i = 0;
	while (ff[i].name[0])
	{
		if (ff[i].iter == *iter)
			ok_ffsig(head, &ff[i]);
		++i;
	}
	i = 0;
	while (con[i].name[0])
	{
		j = 0;
		while (con[i].source[j])
		{
			//ft_printf("??? i %i j %i name %s source %s iter %i\n", i, j, con[i].name, con[i].source[j], con[i].iter[j]);
			if (con[i].iter[j] == *iter)
				ok_consig(head, &con[i]);
			++j;
		}
		++i;
	}
}

void	ok_processsig(t_list **oldhead, t_ff ff[50], t_con con[50], int *iter, long long *high, long long *low)
{
	t_list		*newhead;
	t_list		*tmp;
	t_signal	*signal;

	tmp = *oldhead;
	while (tmp)
	{
		signal = tmp->content;
		if (signal->signal == HIGH)
			++(*high);
		else if (signal->signal == LOW)
			++(*low);
		if (signal->signal == HIGH)
			ft_printf("from %s -high--> %s\n", signal->from, signal->to);
		else if (signal->signal == LOW)
			ft_printf("from %s --low--> %s\n", signal->from, signal->to);
		else
			ft_printf("signal %i WTF??? from %s to %s\n", signal->signal, signal->from, signal->to);
		ok_executesig(signal, ff, con, iter);
		tmp = tmp->next;
	}
	ft_lstclear(oldhead, free);
	newhead = NULL;
	ok_createlist(&newhead, ff, con, iter);
	++(*iter);
	ft_printf("%^*Clow %5lli     high %5lli %C\n", 0x007777, *low, *high);
	ft_printf("%^*C    ITER     %-14i   %C\n", 0x007777, *iter);
	*oldhead = newhead;
}

long long ok_runsignals(t_broadcast *broad, t_ff ff[50], t_con con[50])
{
	long long	low;
	long long	high;
	int			signals;
	int			j;
	int			iter;
	t_list		*sig;

	signals = 0;
	high = 0;
	low = 0;
	iter = 1;
	while (signals < RUNS)
	{
		ft_printf("%^*C    RUN %-14i                %C\n", 0x770077, signals);
		sig = NULL;
		low += 1;
		++iter;
		j = 0;
		while (broad->targets[j])
		{
			ok_createsignal(&sig, broad->targets[j], NULL, LOW);
			++j;
		}
		while (sig)
		{
			ok_processsig(&sig, ff, con, &iter, &high, &low);
		}
		++signals;
		ft_printf("low %5lli      high %5lli\n", low, high);
	}
	return (high * low);
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
			ok_createbroad(&broad, line[j]);
		}
		++j;
	}
	ff[f].name[0] = 0;
	con[c].name[0] = 0;
	ok_updatecon(ff, con, f, c);
	ft_printf("broadcast -> ");
	j = 0;
	while (broad.targets[j])
		ft_printf("%s ", broad.targets[j++]);
	ft_printf("\n");
	i = 0;
	while (i < c)
	{
		j = 0;		
		while (con[i].source[j])
			ft_printf(" %s ", con[i].source[j++]);
		ft_printf(" -> con %s -> ", con[i].name);
		j = 0;
		while (con[i].targets[j])
			ft_printf("%s ", con[i].targets[j++]);
		ft_printf("\n");
		++i;
	}
	i = 0;
	while (i < f)
	{
		j = 0;		
		ft_printf("ff %s -> ", ff[i].name);
		j = 0;
		while (ff[i].targets[j])
			ft_printf("%s ", ff[i].targets[j++]);
		ft_printf("\n");
		++i;
	}
	r = ok_runsignals(&broad, ff, con);
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
	//816870672 too low
	ft_printf("t2=%5lld\n", total[1]);
	ft_free_split(&line);
	return (0);
}
//797259120 low