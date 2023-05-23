/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:14:06 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/23 19:35:48 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_over(t_ph *ph)
{
	int	i;
	int	b;
	int	onedied;
	
	onedied = 0;
	while (!(ph->ph->rule))
	{
		i = 0;
		while (i < ph->ph->infph.nbr_philo && !ph->ph[i].isdead)
		{
			if (!onedied && is_dead(ph, i) == 1)
			{
				onedied = 1;
				return (1);
			}
			usleep(100);
			i++;
		}
	pthread_mutex_lock(&ph->ph[0].fork[ph->ph[0].meat]);
	b = 0;
	while (b < ph->ph[0].infph.nbr_philo && ph->ph[0].maxeat >= ph->ph[0].infph.loop)
		b++;
	pthread_mutex_unlock(&ph->ph[0].fork[ph->ph[0].meat]);
	if (b == ph->ph[0].infph.nbr_philo)
		ph->ph->rule = 1;
	}
	return (1);
}

int	is_dead(t_ph *ph, int i)
{
	long int	time;
	int			tdie;


	tdie = ph->ph[i].infph.tdie;
	time = timestamp();
	pthread_mutex_lock(&ph->ph[i].fork[ph->ph[i].meat]);
	if (time - ph->ph[i].lasteat >= tdie && ph->ph[i].rule != 1)
	{
		pthread_mutex_lock(&ph->ph[i].fork[ph->ph->speak]);
		printf("%ld [%d] \033[91mdied\033[0m\n", \
			time - ph->ph[i].stimer, ph->ph[i].id);
		setruleone(ph);
		pthread_mutex_unlock(&ph->ph[i].fork[ph->ph->speak]);
		return (pthread_mutex_unlock(&ph->ph[i].fork[ph->ph[i].meat]), 1);
	}
	pthread_mutex_unlock(&ph->ph[i].fork[ph->ph->meat]);
	usleep(100);
	return (0);
}

void	setruleone(t_ph *ph)
{
	int i;

	i = 0;
	while (i < ph->ph->infph.nbr_philo)
	{
		ph->ph[i].isdead = 1;
		i++;
	}
}

void	philo(char **av)
{
	t_ph		ph;
	int			i;
	pthread_t	*threads;

	i = 0;
	getinfo(&ph, av);
	threads = malloc(sizeof(pthread_t) * ph.ph->infph.nbr_philo);
	if (!threads)
		return (free(ph.ph));
	init_mutex(&ph);
	while (i < ph.ph->infph.nbr_philo)
	{
		pthread_create(&threads[i], NULL, get_time, &ph.ph[i]);
		i++;
	}
	is_over(&ph);
	ft_usleep((ph.ph->infph.tdie + ph.ph->infph.teat + ph.ph->infph.tsleep) * 2);
	destroy_philo(&ph, threads);
}

int	main(int argc, char **argv)
{
	(void) argc;
	if (argc < 5 || argc > 6)
		return (nbrargs());
	philo(argv);
	return (0);
}
