/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:14:06 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/16 16:44:21 by hdiot            ###   ########.fr       */
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
		ph->ph[b].infph.tdie = ft_atoi(av[2]);
		ph->ph[b].infph.teat = ft_atoi(av[3]);
		ph->ph[b].infph.tsleep = ft_atoi(av[4]);
		if (av[5])
			ph->ph[b].infph.loop = ft_atoi(av[5]);
		else
			ph->ph[b].infph.loop = -1;
		b++;
	}		
	checkvalue(ph);
}

void	*get_time(void *info)
{
	t_philo	*ph;

	ph = (t_philo *)info;
	ph->curloop = 0;
	if (ph->id % 2 == 0)
		ph->timer += ft_usleep(10);
	printf("LFORK %d RFORK %d\n", ph->l_fork, ph->r_fork);
	printf("lfork ADRESS %p rfork ADRESS %p\n", &ph->fork[ph->l_fork], &ph->fork[ph->r_fork]);
	while (ph->curloop < ph->infph.loop)
	{
		ph->curloop++;
		eating(ph);
		if (ph->curloop == ph->infph.loop)
			break ;
		sleepthink(ph);
	}
	return (info);
}

void	init_mutex(t_ph *ph)
{
	int	i;
	int	b;

	i = 0;
	b = ph->ph->infph.nbr_philo;
	printf("B IS %d\n", b);
	if (pthread_mutex_init(&ph->ph->speak, NULL) != 0)
		printf("Failed to init speak mutex\n");
	ph->ph->fork = malloc(sizeof(pthread_mutex_t) * b);
	if (!ph->ph->fork)
		printf("Failed to malloc fork mutex\n");
	if (pthread_mutex_init(ph->ph->fork, NULL) != 0)
		printf("Failed to init fork mutex\n");
	while (i < b)
	{
		ph->ph[i].l_fork = i;
		ph->ph[i].r_fork = i + 1;
		i++;
	}
}

void	destroy_philo(t_ph *ph, pthread_t *threads)
{
	int	i;
	int	b;

	i = 0;
	b = ph->ph[0].infph.nbr_philo;
	if (pthread_mutex_destroy(&ph->ph->speak) < 0)
		printf("Failed to destroy\n");
	pthread_mutex_destroy(ph->ph->fork);
	free(threads);
	free(ph->ph);
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
		printf("lfork ADRESS %p rfork ADRESS %p\n", &ph.ph->fork[i], &ph.ph->fork[i + 1]);
		pthread_create(&threads[i], NULL, get_time, &ph.ph[i]);
		i++;
		ft_usleep(50);
	}
	i = 0;
	while (i < ph.ph->infph.nbr_philo)
	{	
		pthread_detach(threads[i]);
		i++;
	}
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