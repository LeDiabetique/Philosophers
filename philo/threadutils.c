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

void	speaking(t_philo *ph, char *str)
{
	pthread_mutex_lock(&(ph->fork[ph->speak]));
	ph->timer = timestampdiff(ph->stimer);
	if (!(ph->isdead))
		printf("%ld [%d] %s\n", ph->timer, ph->id, str);
	pthread_mutex_unlock(&(ph->fork[ph->speak]));
}

int	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->fork[ph->l_fork]);
	speaking(ph, "\033[92mhas taken a fork\033[0m");
	if (ph->infph.nbr_philo == 1)
	{
		ft_usleep(ph->infph.tdie);
		return (pthread_mutex_unlock(&ph->fork[ph->l_fork]), 1);
	}	
	pthread_mutex_lock(&ph->fork[ph->r_fork]);
	speaking(ph, "\033[92mhas taken a fork\033[0m");
	pthread_mutex_lock(&ph->fork[ph->meat]);
	speaking(ph, "\033[93mis eating\033[0m");
	ph->lasteat = timestamp();
	pthread_mutex_unlock(&ph->fork[ph->meat]);
	ft_usleep(ph->infph.teat);
	pthread_mutex_lock(&ph->fork[ph->meat]);
	ph->maxeat++;
	pthread_mutex_unlock(&ph->fork[ph->meat]);
	pthread_mutex_unlock(&ph->fork[ph->l_fork]);
	pthread_mutex_unlock(&ph->fork[ph->r_fork]);
	return (0);
}

int	sleepthink(t_philo *ph)
{
	speaking(ph, "\033[95mis sleeping\033[0m");
	ft_usleep(ph->infph.tsleep);
	speaking(ph, "\033[94mis thinking\033[0m");
	return (0);
}
