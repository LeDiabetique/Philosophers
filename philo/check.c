/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:02:14 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/24 10:04:03 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	badargsexit(void)
{
	ft_putstr_fd("Bad args, only positives digits near 1 - MAXINT allowed\n", 2);
	return ;
}

long int	timestamp(void)
{
	struct timeval	time;
	long int		acttime;

	gettimeofday(&time, NULL);
	acttime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (acttime);
}

int	checkmaxint(char *str)
{
	if (ft_strlen(str) == 9)
	{
		if (str[0] > '2')
			return (badargsexit(), 1);
		if (str[1] > '1')
			return (badargsexit(), 1);
		if (str[2] > '4')
			return (badargsexit(), 1);
		if (str[3] > '7')
			return (badargsexit(), 1);
		if (str[4] > '4')
			return (badargsexit(), 1);
		if (str[5] > '8')
			return (badargsexit(), 1);
		if (str[6] > '3')
			return (badargsexit(), 1);
		if (str[7] > '6')
			return (badargsexit(), 1);
		if (str[8] > '4')
			return (badargsexit(), 1);
		if (str[9] > '7')
			return (badargsexit(), 1);
	}
	return (0);
}

int	checkvalue(t_ph *ph)
{
	if (ph->ph->infph.nbr_philo <= 0 || ph->ph->infph.tdie <= 0
		|| ph->ph->infph.teat <= 0 || ph->ph->infph.tsleep <= 0)
	{
		printf("Bad args, only positives digits \
			near 1 and MAXINT are allowed\n");
		return (1);
	}
	if (ph->ph->infph.loop < -1 || ph->ph->infph.loop == 0)
	{
		printf("Bad args, only positives digits \
			near 1 and MAXINT are allowed\n");
		return (1);
	}
	return (0);
}

int	checkdigits(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (ft_strlen(av[i]) > 10)
			return (badargsexit(), 1);
		while (av[i][j])
		{
			if (ft_isdigit((int)av[i][j]) == 0)
			{
				printf("Bad args, only digits are allowed\n");
				return (1);
			}
			j++;
		}
		if (checkmaxint(av[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
