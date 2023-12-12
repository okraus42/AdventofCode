/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p1.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 06:38:26 by okraus            #+#    #+#             */
/*   Updated: 2023/12/02 06:05:18 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/header/libft.h"
#include <sys/stat.h>
#include <fcntl.h>

void	ok_update(char *str, int *pfirst, int *plast)
{
	char	f;
	char	l;
	int		i;

	i = 0;
	f = 0;
	while(str[i])
	{
		if (!f && ft_isdigit(str[i]))
		{
			f = str[i];
		}
		if (ft_isdigit(str[i]))
		{
			l = str[i];
		}
		++i;
	}
	*pfirst = (f - '0') * 10;
	*plast = l - '0';
}

char	ok_istextdigit(char *str)
{
	if (!ft_strncmp(str, "one", 3))
		return ('1');
	else if (!ft_strncmp(str, "two", 3))
		return ('2');
	else if (!ft_strncmp(str, "three", 5))
		return ('3');
	else if (!ft_strncmp(str, "four", 4))
		return ('4');
	else if (!ft_strncmp(str, "five", 4))
		return ('5');
	else if (!ft_strncmp(str, "six", 3))
		return ('6');
	else if (!ft_strncmp(str, "seven", 5))
		return ('7');
	else if (!ft_strncmp(str, "eight", 5))
		return ('8');
	else if (!ft_strncmp(str, "nine", 4))
		return ('9');
	else
		return (0);
}

void	ok_update2(char *str, int *pfirst, int *plast)
{
	char	f;
	char	l;
	int		i;

	i = 0;
	f = 0;
	while(str[i])
	{
		if (!f && ft_isdigit(str[i]))
		{
			f = str[i];
		}
		if (!f && ok_istextdigit(&str[i]))
		{
			f = ok_istextdigit(&str[i]);
		}
		if (ft_isdigit(str[i]))
		{
			l = str[i];
		}
		if (ok_istextdigit(&str[i]))
		{
			l = ok_istextdigit(&str[i]);
		}
		++i;
	}
	*pfirst = (f - '0') * 10;
	*plast = l - '0';
}

int	main(void)
{
	int 	fd;
	char	*line;
	int		first;
	int		last;
	int		total[2];

	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	total[0] = 0;
	total[1] = 0;
	while (line)
	{
		ok_update(line, &first, &last);
		total[0] += first;
		total[0] += last;
		ft_printf("f=%d, l = %d, t1=%5d\n", first, last, total[0]);
		ok_update2(line, &first, &last);
		total[1] += first;
		total[1] += last;
		ft_printf("f=%d, l = %d, t2=%5d\n", first, last, total[1]);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
