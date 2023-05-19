/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:14:06 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/19 15:31:50 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_over(t_ph *ph)
{
	int i;
	int eat;
	int max;

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
			max++;
		}
		pthread_mutex_unlock(&ph->ph[i].fork[ph->ph->meat]);
		if (max == eat)
			return (1);
		i++;
	}
	return (1);
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
	   // printf("[%d] LFORK %p RFORK %p\n", ph.ph[i].id, &ph.ph[i].fork[ph.ph[i].l_fork], &ph.ph[i].fork[ph.ph[i].r_fork]);
		//printf("[%d] speak %p meat %p\n", ph.ph[i].id, &ph.ph[i].fork[ph.ph[i].speak], &ph.ph[i].fork[ph.ph[i].meat]);
		pthread_create(&threads[i], NULL, get_time, &ph.ph[i]);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < ph.ph->infph.nbr_philo)
		pthread_detach(threads[i++]);
	while (!is_over(&ph))
		;
	destroy_philo(&ph, threads);
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