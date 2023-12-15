/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p15.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/15 07:34:15 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

typedef struct s_lens
{
	char	label[12];
	int		foc;
}	t_lens;

typedef struct s_box
{
	t_list	*lens;
}	t_box;

int	ok_counthash(char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (str[i])
	{
		result += (str[i]);
		result *= 17;
		result %= 256;
		++i;
	}
	//ft_printf("%i\n", result);
	return (result);
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	j = 0;
	while (line[j])
	{
		*ptot += ok_counthash(line[j]);
		++j;
	}
	(void)i;
}

void	ok_addlens(char *str, t_list **head)
{
	t_list	*new;
	t_list	*tmp;
	t_lens	*lens;
	t_lens	*content;
	int		i;

	lens = ft_calloc(sizeof(lens), 1);
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '-')
	{
		lens->label[i] = str[i];
		++i;
	}
	lens->label[i] = 0;
	++i;
	lens->foc = ft_atoi(&str[i]);
	tmp = *head;
	while (tmp)
	{
		content = tmp-> content;
		if (!ft_strncmp(content->label, lens->label, 11))
		{
			content->foc = lens->foc;
			free(lens);
			return ;
		}
		tmp = tmp->next;
	}
	new = ft_lstnew(lens);
	ft_lstadd_back(head, new);
}

void	ok_removelens(char *str, t_list **head)
{
	t_list	*tmp;
	t_list	*ntmp;
	t_list	*ptmp;
	t_lens	*content;
	char	label[12];
	int		i;

	if (!(*head))
		return ;
	i = 0;
	while (str[i] && str[i] != '-' && str[i] != '=')
	{
		label[i] = str[i];
		++i;
	}
	label[i] = 0;
	tmp = *head;
	ptmp = NULL;
	while (tmp)
	{
		//ft_printf("1 %p %p\n", tmp, ptmp);
		content = tmp->content;
		if (!ft_strncmp(content->label, label, 11))
		{
			ntmp = tmp->next;
			//ft_printf("2%p %p\n", tmp, ptmp);
			ft_lstdelone(tmp, free);
			tmp = NULL;
			if (ptmp)
			{
				ptmp->next = ntmp;
			}
			else
				*head = ntmp;
			return ;
		}
		ptmp = tmp;
		tmp = tmp->next;
	}
	//ft_printf("4 %p %p\n", tmp, ptmp);
}

void	ok_sortlens(char *str, t_box box[256])
{
	int	i;
	int	h;

	i = 0;
	h = 0;
	while (str[i] && str[i] != '=' && str[i] != '-')
	{
		h += (str[i]);
		h *= 17;
		h %= 256;
		++i;
	}
	//ft_printf("%i\n", h);
	if (str[i] == '=')
	{
		ok_addlens(str, &(box[h].lens));
	}
	else if (str[i] == '-')
	{
		ok_removelens(str, &(box[h].lens));
	}
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	t_box	box[256];
	t_list	*tmp;
	t_lens	*lens;

	j = 0;
	i = 0;
	while (i < 256)
	{
		box[i].lens = NULL;
		++i;
	}
	while (line[j])
	{
		ok_sortlens(line[j], box);
		++j;
	}
	i = 0;
	j = 0;
	//ft_printf("test\n");
	while (i < 256)
	{
		j = 0;
		tmp = box[i].lens;
		++i;
		while(tmp)
		{
			lens = tmp->content;
			++j;
			ft_printf("%i %i %i %i\n", i, j, lens->foc, (i) * j * lens->foc);
			*ptot += (i) * j * lens->foc;
			tmp = tmp->next;
		}
	}
}

int	main(void)
{
	char		**line;
	char		**lines;
	int			i;
	int			j;
	long long	total[2];

	total[0] = 0;
	total[1] = 0;
	line = NULL;
	i = 1;
	line = ft_readfile("input", 65536);
	lines = ft_split(line[0], ',');
	//ft_printf("%p\n", (void *)line);
	//ft_printf("j = %i\n", j);
	i = 0;
	j = 0;
	ok_update(lines, &total[0], i, j);
	ft_printf("t1=%5lld\n", total[0]);
	ok_update2(lines, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	return (0);
}
