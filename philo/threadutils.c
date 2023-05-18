/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:24:24 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/17 12:05:56 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	timestamp(void)
{
	struct timeval	time;
	long int		acttime;

	gettimeofday(&time, NULL);
	acttime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (acttime);
}

long int	ft_usleep(int tlimit)
{
	long int	time;

	time = 0;
	time = timestamp();
	while ((timestamp() - time) < tlimit)
		usleep(tlimit / 10);
	return (timestamp() - time);
}

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->speak);
	pthread_mutex_lock(&ph->fork[ph->l_fork]);
	printf("%ld [%d] \033[92mhas taken a fork\033[0m\n", ph->timer, ph->id);
	pthread_mutex_unlock(&ph->speak);
	pthread_mutex_lock(&ph->fork[ph->r_fork]);
	pthread_mutex_lock(&ph->speak);
	printf("%ld [%d] \033[92mhas taken a fork\033[0m\n", ph->timer, ph->id);
	printf("%ld [%d] \033[93mis eating\033[0m\n", ph->timer, ph->id);
	if (ph->infph.nbr_philo == 1)
		ph->timer = ft_usleep(ph->infph.tdie);
	pthread_mutex_unlock(&ph->speak);
	ph->timer += ft_usleep(ph->infph.teat);
	pthread_mutex_unlock(&ph->fork[ph->r_fork]);
	pthread_mutex_unlock(&ph->fork[ph->l_fork]);
}

void	sleepthink(t_philo *ph)
{
	pthread_mutex_lock(&ph->speak);
	printf("%ld [%d] \033[94mis sleeping\033[0m\n", ph->timer, ph->id);
	pthread_mutex_unlock(&ph->speak);
	ph->timer += ft_usleep(ph->infph.tsleep);
	pthread_mutex_lock(&ph->speak);
	printf("%ld [%d] \033[95mis thinking\033[0m\n", ph->timer, ph->id);
	pthread_mutex_unlock(&ph->speak);
}