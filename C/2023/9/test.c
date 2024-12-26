/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:55:35 by okraus            #+#    #+#             */
/*   Updated: 2023/12/09 14:59:37 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	testarr(int arr[20][20])
{
	int	i;
	int	j;

	j = 0;
	while (j < 20)
	{
		i = 0;
		while (i < 20)
		{
			arr[j][i] = i * j;
			++i;
		}
		++j;
	}
}

int	main(void)
{
	int	arr[20][20];
	int	i;
	int	j;

	j = 0;
	while (j < 20)
	{
		i = 0;
		while (i < 20)
		{
			arr[j][i] = 0;
			++i;
		}
		++j;
	}
	testarr(arr);
	ft_printf("arr[19][19] = %i\n", arr[19][19]);
	return (0);
}
