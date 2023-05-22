/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:24:52 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/22 15:16:01 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	getinfo(t_ph *ph, char **av)
{
	int	i;
	int	b;

	checkdigits(av);
	i = ft_atoi(av[1]);
	ph->ph = malloc(sizeof(t_philo) * i);
	b = 0;
	while (b < i)
	{
		ph->ph[b].infph.nbr_philo = i;
		ph->ph[b].id = b + 1;
		ph->ph[b].timer = 0;
		ph->ph[b].maxeat = 0;
		ph->ph[b].dead = 0;
		ph->ph[b].rule = 0;
		ph->ph[b].stimer = timestamp();
		ph->ph[b].lasteat = ph->ph[b].stimer;
		ph->ph[b].infph.tdie = ft_atoi(av[2]);
		ph->ph[b].infph.teat = ft_atoi(av[3]);
		ph->ph[b].infph.tsleep = ft_atoi(av[4]);
		if (av[5])
			ph->ph[b++].infph.loop = ft_atoi(av[5]);
		else
			ph->ph[b++].infph.loop = 2147483647;
	}
	checkvalue(ph);
}

void 	threadunlock(t_philo *ph)
{
	pthread_mutex_unlock(&ph->fork[ph->meat]);
	pthread_mutex_unlock(&ph->fork[ph->l_fork]);
	pthread_mutex_unlock(&ph->fork[ph->r_fork]);
	pthread_mutex_unlock(&ph->fork[ph->speak]);
	pthread_mutex_unlock(&ph->fork[ph->dead]);
}

void	*get_time(void *info)
{
	t_philo	*ph;

	ph = (t_philo *)info;
	ph->curloop = 0;
	if (ph->id % 2 == 0)
		ft_usleep(ph->infph.teat / 2);
	ph->timer = timestampdiff(ph->stimer);
	while (ph->rule == 0)
	{
		ph->curloop++;
		if (eating(ph) == 1)
			return (threadunlock(ph), info);
		if (ph->curloop == ph->infph.loop)
		{
			pthread_mutex_lock(&ph->fork[ph->meat]);
			ph->maxeat = 1;
			pthread_mutex_unlock(&ph->fork[ph->meat]);
			break ;
		}	
		if (sleepthink(ph) == 1)
			return (threadunlock(ph), info);
	}
	return (threadunlock(ph), info);
}

void	init_mutex(t_ph *ph)
{
	int	i;
	int	b;

	i = 0;
	b = ph->ph->infph.nbr_philo;
	ph->ph->fork = malloc(sizeof(pthread_mutex_t) * (b + 3));
	if (!ph->ph->fork)
		printf("Failed to malloc fork mutex\n");
	while (i < b + 3)
	{
		if (pthread_mutex_init(&ph->ph->fork[i], NULL) != 0)
			printf("Failed to init fork mutex\n");
		i++;
	}
	i = 0;
	while (i < b)
	{
		ph->ph[i].l_fork = i;
		ph->ph[i].r_fork = (i + 1) % b;
		ph->ph[i].fork = ph->ph->fork;
		ph->ph[i].speak = b;
		ph->ph[i].meat = b + 1;
		ph->ph[i].dead = b + 2;
		i++;
	}
}

void	destroy_philo(t_ph *ph, pthread_t *threads)
{
	int	i;
	int	b;

	i = 0;
	b = ph->ph->infph.nbr_philo;
	while (i < b + 3)
	{
		if (pthread_mutex_destroy(&ph->ph->fork[i]) != 0)
		{	
			pthread_mutex_unlock(&ph->ph->fork[i]);
			if (pthread_mutex_destroy(&ph->ph->fork[i]) != 0)
				printf("Failed to destroy fork [%d] mutex\n", i);
		}
		i++;
	}
	free(threads);
	free(ph->ph->fork);
	free(ph->ph);
}
