/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:24:24 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/24 10:38:16 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_usleep(int limit)
{
	long int	time;
	long int	end;
	long int	result;

	time = 0;
	time = timestamp();
	result = time;
	end = time + limit;
	usleep(limit * 1000 * 70 / 100);
	while (end - time > 0)
	{	
		usleep(100);
		time = timestamp();
	}
	return (time - result);
}

long int	timestamp_diff(long int start)
{
	long int	new_time;
	long int	actual_time;

	actual_time = 0;
	actual_time = timestamp();
	new_time = actual_time - start;
	return (new_time);
}

void	speaking(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->mutex_array[philo->speak]));
	philo->timer = timestamp_diff(philo->start_timer);
	if (!(philo->is_dead))
		printf("%ld [%d] %s\n", philo->timer, philo->id, str);
	pthread_mutex_unlock(&(philo->mutex_array[philo->speak]));
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_array[philo->left_fork]);
	speaking(philo, "\033[92mhas taken his left fork\033[0m");
	if (philo->info_philo.nbr_philo == 1)
	{
		ft_usleep(philo->info_philo.time_to_die);
		return (pthread_mutex_unlock(&philo->mutex_array[philo->left_fork]), 1);
	}	
	pthread_mutex_lock(&philo->mutex_array[philo->right_fork]);
	speaking(philo, "\033[92mhas taken his right fork\033[0m");
	pthread_mutex_lock(&philo->mutex_array[philo->mutex_eat]);
	speaking(philo, "\033[93mis eating\033[0m");
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&philo->mutex_array[philo->mutex_eat]);
	ft_usleep(philo->info_philo.time_to_eat);
	pthread_mutex_lock(&philo->mutex_array[philo->mutex_eat]);
	philo->max_eat++;
	pthread_mutex_unlock(&philo->mutex_array[philo->mutex_eat]);
	pthread_mutex_unlock(&philo->mutex_array[philo->left_fork]);
	pthread_mutex_unlock(&philo->mutex_array[philo->right_fork]);
	return (0);
}

int	sleep_think(t_philo *philo)
{
	speaking(philo, "\033[95mis sleeping\033[0m");
	ft_usleep(philo->info_philo.time_to_sleep);
	speaking(philo, "\033[94mis thinking\033[0m");
	return (0);
}
