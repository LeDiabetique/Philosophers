/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:24:24 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/19 16:49:15 by hdiot            ###   ########.fr       */
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
	//printf("%ld - %ld = %ld\n", time, res, time - res);
	return (time - res);
}

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->fork[ph->l_fork]);
	pthread_mutex_lock(&ph->fork[ph->speak]);
	ph->timer = timestamp() - ph->timer;
	printf("%ld [%d] \033[92mhas taken a lfork \033[0m\n", ph->timer, ph->id);
	pthread_mutex_unlock(&ph->fork[ph->speak]);
	pthread_mutex_lock(&ph->fork[ph->r_fork]);
	pthread_mutex_lock(&ph->fork[ph->speak]);
	ph->timer = timestamp() - ph->timer;
	printf("%ld [%d] \033[92mhas taken a rfork \033[0m\n", ph->timer, ph->id);
	ph->timer = timestamp() - ph->timer;
	printf("%ld [%d] \033[93mis eating\033[0m\n", ph->timer, ph->id);
	pthread_mutex_unlock(&ph->fork[ph->speak]);
	if (ph->infph.nbr_philo == 1)
		ft_usleep(ph->infph.tdie);
	ft_usleep(ph->infph.teat);
	ph->timer = timestamp() - ph->timer;
	pthread_mutex_unlock(&ph->fork[ph->l_fork]);
	pthread_mutex_unlock(&ph->fork[ph->r_fork]);
}

void	sleepthink(t_philo *ph)
{
	pthread_mutex_lock(&ph->fork[ph->speak]);
	ph->timer = timestamp() - ph->timer;
	printf("%ld [%d] \033[94mis sleeping\033[0m\n", ph->timer, ph->id);
	pthread_mutex_unlock(&ph->fork[ph->speak]);
	ft_usleep(ph->infph.tsleep);
	ph->timer = timestamp() - ph->timer;
	pthread_mutex_lock(&ph->fork[ph->speak]);
	ph->timer = timestamp() - ph->timer;
	printf("%ld [%d] \033[95mis thinking\033[0m\n", ph->timer, ph->id);
	pthread_mutex_unlock(&ph->fork[ph->speak]);
}