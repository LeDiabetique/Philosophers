/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:14:06 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/15 15:02:19 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	getinfo(t_ph *ph, char **av)
{
	int	i;

	checkdigits(av);
	i = ft_atoi(av[1]);
	ph->ph = malloc(sizeof(t_philo) * i);
	ph->ph->infph.nbr_philo = i;
	ph->ph->infph.tdie = ft_atoi(av[2]);
	ph->ph->infph.teat = ft_atoi(av[3]);
	ph->ph->infph.tsleep = ft_atoi(av[4]);
	if (av[5])
		ph->ph->infph.loop = ft_atoi(av[5]);
	else
		ph->ph->infph.loop = -1;
	checkvalue(ph);
}

void	*get_time(void *info)
{
	t_philo	*ph;

	ph = (t_philo *)info;
	ph->curloop = 0;
	if (ph->id % 2 == 0)
		ph->timer += ft_usleep(ph->infph.teat);
	while (ph->curloop < ph->infph.loop)
	{
		eating(ph);
		sleepthink(ph);
		ph->curloop++;
	}
	return (info);
}

void	init_mutex(t_ph *ph)
{
	pthread_mutex_init(&ph->ph->speak, NULL);
	pthread_mutex_init(&ph->ph->l_fork, NULL);
	ph->ph->r_fork = malloc(sizeof(pthread_mutex_t));
	if (!ph->ph->r_fork)
		exit(EXIT_FAILURE);
	pthread_mutex_init(ph->ph->r_fork, NULL);
}

void	philo(char **av)
{
	t_ph		ph;
	int			i;
	pthread_t	*threads;
	t_philo		*test;

	i = 0;
	getinfo(&ph, av);
	ph.ph->timer = 0;
	threads = malloc(sizeof(pthread_t) * ph.ph->infph.nbr_philo);
	test = malloc(sizeof(t_philo) * ph.ph->infph.nbr_philo);
	init_mutex(&ph);
	while (i < ph.ph->infph.nbr_philo)
	{
		ph.ph[i].id = i + 1;
		test[i] = ph.ph[i];
		pthread_create(&threads[i], NULL, get_time, &test[i]);
		i++;
	}
	i = 0;
	while (i < ph.ph->infph.nbr_philo)
	{	
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&ph.ph->speak);
	pthread_mutex_destroy(&ph.ph->l_fork);
	pthread_mutex_destroy(ph.ph->r_fork);
	free(ph.ph);
	free(threads);
	free(test);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (nbrargs());
	philo(argv);
	return (0);
}