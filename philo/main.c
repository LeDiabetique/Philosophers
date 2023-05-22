/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:14:06 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/22 16:42:55 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_over(t_ph *ph)
{
	int	eat;
	int	i;
	int	max;

	i = 0;
	eat = ph->ph->infph.nbr_philo;
	max = 0;
	while (max != eat)
	{
		if (i == ph->ph->infph.nbr_philo)
			i = 0;
		pthread_mutex_lock(&ph->ph[i].fork[ph->ph->meat]);
		if (ph->ph[i].maxeat == 1)
		{
			ph->ph[i].maxeat = 2;
			ph->ph[i].rule = 1;
			max++;
		}
		pthread_mutex_unlock(&ph->ph[i].fork[ph->ph->meat]);
		if (max == eat)
			return (pthread_mutex_lock(&ph->ph[i].fork[ph->ph->speak]), 1);	
		if (is_dead(ph, i) == 1)
		{
			i = 0;
			while (i < ph->ph->infph.nbr_philo)
				pthread_mutex_destroy(&ph->ph[i++].fork[ph->ph->speak]);
			return (1);
		}	
		i++;
	}
	return (1);
}

int	is_dead(t_ph *ph, int i)
{
	long int	time;
	int			tdie;

	tdie = ph->ph[i].infph.tdie;
	time = timestamp();
	pthread_mutex_lock(&ph->ph[i].fork[ph->ph->dead]);
	if (time - ph->ph[i].lasteat >= tdie)
	{
		pthread_mutex_lock(&ph->ph[i].fork[ph->ph->irule]);
		if (ph->ph[i].rule == 1)
			return (pthread_mutex_unlock(&ph->ph[i].fork[ph->ph->irule]), 1);
		pthread_mutex_unlock(&ph->ph[i].fork[ph->ph->irule]);
		pthread_mutex_lock(&ph->ph[i].fork[ph->ph->speak]);
		printf("%ld [%d] \033[91mdied\033[0m\n", \
			time - ph->ph[i].stimer, ph->ph[i].id);
		setruleone(ph);
		return (pthread_mutex_unlock(&ph->ph[i].fork[ph->ph->dead]), 1);
	}
	pthread_mutex_unlock(&ph->ph[i].fork[ph->ph->dead]);
	return (0);
}

void	setruleone(t_ph *ph)
{
	int i;

	i = 0;
	while (i < ph->ph->infph.nbr_philo)
	{
		pthread_mutex_lock(&ph->ph[i].fork[ph->ph->irule]);
		ph->ph[i].rule = 1;
		pthread_mutex_unlock(&ph->ph[i].fork[ph->ph->irule]);
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
	i = 0;
	while (i < ph.ph->infph.nbr_philo)
		pthread_detach(threads[i++]);
	while (is_over(&ph) == 0)
		;
	destroy_philo(&ph, threads);
	//ft_usleep(ph.ph->infph.tdie + ph.ph->infph.teat + ph.ph->infph.tsleep);
	printf("FINITO\n");
}

int	main(int argc, char **argv)
{
	(void) argc;
	if (argc < 5 || argc > 6)
		return (nbrargs());
	philo(argv);
	return (0);
}
