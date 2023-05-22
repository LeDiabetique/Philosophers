/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:02:14 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/22 10:09:23 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	badargsexit(void)
{
	ft_putstr_fd("Bad args, only positives digits near 1 - MAXINT allowed\n", 2);
	exit(EXIT_FAILURE);
}

void	checkmaxint(char *str)
{
	if (ft_strlen(str) > 10)
		badargsexit();
	if (ft_strlen(str) == 9)
	{
		if (str[0] > '2')
			badargsexit();
		if (str[1] > '1')
			badargsexit();
		if (str[2] > '4')
			badargsexit();
		if (str[3] > '7')
			badargsexit();
		if (str[4] > '4')
			badargsexit();
		if (str[5] > '8')
			badargsexit();
		if (str[6] > '3')
			badargsexit();
		if (str[7] > '6')
			badargsexit();
		if (str[8] > '4')
			badargsexit();
		if (str[9] > '7')
			badargsexit();
	}
}

void	checkvalue(t_ph *ph)
{
	if (ph->ph->infph.nbr_philo <= 0 || ph->ph->infph.tdie <= 0
		|| ph->ph->infph.teat <= 0 || ph->ph->infph.tsleep <= 0)
	{
		printf("Bad args, only positives digits \
			near 1 and MAXINT are allowed\n");
		exit(EXIT_FAILURE);
	}
	if (ph->ph->infph.loop < -1 || ph->ph->infph.loop == 0)
	{
		printf("Bad args, only positives digits \
			near 1 and MAXINT are allowed\n");
		exit(EXIT_FAILURE);
	}
}

void	checkdigits(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit((int)av[i][j]) == 0)
			{
				printf("Bad args, only digits are allowed\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		checkmaxint(av[i]);
		i++;
	}
}
