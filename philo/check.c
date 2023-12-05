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

void	bad_args_exit(void)
{
	ft_putstr_fd("Bad args, only positives \
		digits near 1 - MAXINT allowed\n", 2);
	return ;
}

long int	timestamp(void)
{
	struct timeval	time;
	long int		current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}

int	check_max_int(char *str)
{
	if (ft_strlen(str) == 9)
	{
		if (str[0] > '2')
			return (bad_args_exit(), 1);
		if (str[1] > '1')
			return (bad_args_exit(), 1);
		if (str[2] > '4')
			return (bad_args_exit(), 1);
		if (str[3] > '7')
			return (bad_args_exit(), 1);
		if (str[4] > '4')
			return (bad_args_exit(), 1);
		if (str[5] > '8')
			return (bad_args_exit(), 1);
		if (str[6] > '3')
			return (bad_args_exit(), 1);
		if (str[7] > '6')
			return (bad_args_exit(), 1);
		if (str[8] > '4')
			return (bad_args_exit(), 1);
		if (str[9] > '7')
			return (bad_args_exit(), 1);
	}
	return (0);
}

int	check_value(t_ph *philo)
{
	if (philo->philo->info_philo.nbr_philo <= 0 || philo->philo->info_philo.time_to_die <= 0
		|| philo->philo->info_philo.time_to_eat <= 0 || philo->philo->info_philo.time_to_sleep <= 0)
	{
		printf("Bad args, only positives digits \
			near 1 and MAXINT are allowed\n");
		return (1);
	}
	if (philo->philo->info_philo.loop < -1 || philo->philo->info_philo.loop == 0)
	{
		printf("Bad args, only positives digits \
			near 1 and MAXINT are allowed\n");
		return (1);
	}
	return (0);
}

int	check_digits(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (ft_strlen(av[i]) > 10)
			return (bad_args_exit(), 1);
		while (av[i][j])
		{
			if (ft_isdigit((int)av[i][j]) == 0)
			{
				printf("Bad args, only digits are allowed\n");
				return (1);
			}
			j++;
		}
		if (check_max_int(av[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
