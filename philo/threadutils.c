/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:24:24 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/22 15:04:40 by hdiot            ###   ########.fr       */
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
	long int	end;
	long int	res;

	time = 0;
	time = timestamp();
	res = time;
	end = time + tlimit;
	usleep(tlimit * 1000 * 70 / 100);
	while (end - time > 0)
	{	
		usleep(100);
		time = timestamp();
	}
	return (time - res);
}

long int	timestampdiff(long int start)
{
	long int	newtime;
	long int	acttime;

	acttime = 0;
	acttime = timestamp();
	newtime = acttime - start;
	return (newtime);
}

int	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->fork[ph->l_fork]);
	if (ph->rule == 1)
		return (pthread_mutex_unlock(&ph->fork[ph->l_fork]), 1);
	pthread_mutex_lock(&ph->fork[ph->speak]);
	ph->timer = timestampdiff(ph->stimer);
	printf("%ld [%d] \033[92mhas taken a lfork\033[0m\n", ph->timer, ph->id);
	pthread_mutex_unlock(&ph->fork[ph->speak]);
	pthread_mutex_lock(&ph->fork[ph->r_fork]);
	if (ph->rule == 1)
		return (pthread_mutex_unlock(&ph->fork[ph->l_fork]), \
			pthread_mutex_unlock(&ph->fork[ph->r_fork]), 1);
	pthread_mutex_lock(&ph->fork[ph->speak]);
	ph->timer = timestampdiff(ph->stimer);
	printf("%ld [%d] \033[92mhas taken a rfork\033[0m\n", ph->timer, ph->id);
	printf("%ld [%d] \033[93mis eating\033[0m\n", ph->timer, ph->id);
	pthread_mutex_lock(&ph->fork[ph->dead]);
	ph->lasteat = timestamp();
	pthread_mutex_unlock(&ph->fork[ph->dead]);
	pthread_mutex_unlock(&ph->fork[ph->speak]);
	if (ph->infph.nbr_philo == 1)
		ph->timer += ft_usleep(ph->infph.tdie);
	ft_usleep(ph->infph.teat);
	ph->timer = timestampdiff(ph->stimer);
	pthread_mutex_unlock(&ph->fork[ph->l_fork]);
	pthread_mutex_unlock(&ph->fork[ph->r_fork]);
	return (0);
}

int	sleepthink(t_philo *ph)
{
	pthread_mutex_lock(&ph->fork[ph->speak]);
	ph->timer = timestampdiff(ph->stimer);
	printf("%ld [%d] \033[94mis sleeping\033[0m\n", ph->timer, ph->id);
	pthread_mutex_unlock(&ph->fork[ph->speak]);
	ft_usleep(ph->infph.tsleep);
	ph->timer = timestampdiff(ph->stimer);
	pthread_mutex_lock(&ph->fork[ph->speak]);
	ph->timer = timestampdiff(ph->stimer);
	printf("%ld [%d] \033[95mis thinking\033[0m\n", ph->timer, ph->id);
	pthread_mutex_unlock(&ph->fork[ph->speak]);
	return (0);
}
