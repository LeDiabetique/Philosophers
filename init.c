/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:24:52 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/24 09:58:20 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_ph *philo, int b)
{
	philo->philo[b].timer = 0;
	philo->philo[b].max_eat = 0;
	philo->philo[b].is_dead = 0;
	philo->philo[b].rule = 0;
}

int	init_rules(t_ph *philo, char **av)
{
	int	i;
	int	b;

	if (check_digits(av) == 1)
		return (1);
	i = ft_atoi(av[1]);
	philo->philo = malloc(sizeof(t_philo) * i);
	b = 0;
	while (b < i)
	{
		philo->philo[b].info_philo.nbr_philo = i;
		philo->philo[b].id = b + 1;
		init_philo(philo, b);
		philo->philo[b].info_philo.time_to_die = ft_atoi(av[2]);
		philo->philo[b].info_philo.time_to_eat = ft_atoi(av[3]);
		philo->philo[b].info_philo.time_to_sleep = ft_atoi(av[4]);
		if (av[5])
			philo->philo[b++].info_philo.loop = ft_atoi(av[5]);
		else
			philo->philo[b++].info_philo.loop = 2147483647;
	}
	if (check_value(philo) == 1)
		return (1);
	return (0);
}

void	*get_time(void *info)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)info;
	philo->current_loop = 0;
	stop = 0;
	if (philo->id % 2 == 0)
		ft_usleep(philo->info_philo.time_to_eat / 2);
	philo->timer = timestamp_diff(philo->start_timer);
	while (!stop)
	{
		pthread_mutex_lock(&philo->mutex_array[philo->mutex_eat]);
		stop = philo->is_dead;
		pthread_mutex_unlock(&philo->mutex_array[philo->mutex_eat]);
		if (eating(philo) == 1)
			break ;
		if (philo->max_eat == philo->info_philo.loop)
			break ;
		sleep_think(philo);
	}
	return (NULL);
}

void	init_mutex(t_ph *philo)
{
	int	i;
	int	b;

	i = 0;
	b = philo->philo->info_philo.nbr_philo;
	philo->philo->mutex_array = malloc(sizeof(pthread_mutex_t) * (b + 4));
	if (!philo->philo->mutex_array)
		printf("Failed to malloc mutex_array mutex\n");
	while (i < b + 2)
	{
		if (pthread_mutex_init(&philo->philo->mutex_array[i], NULL) != 0)
			printf("Failed to init mutex_array mutex\n");
		i++;
	}
	i = -1;
	while (++i < b)
	{
		philo->philo[i].left_fork = i;
		philo->philo[i].right_fork = (i + 1) % b;
		philo->philo[i].mutex_array = philo->philo->mutex_array;
		philo->philo[i].speak = b;
		philo->philo[i].mutex_eat = b + 1;
		philo->philo[i].start_timer = timestamp();
		philo->philo[i].last_eat = philo->philo[i].start_timer;
	}
}

void	destroy_philo(t_ph *philo, pthread_t *threads)
{
	int	i;
	int	b;

	i = 0;
	b = philo->philo->info_philo.nbr_philo;
	while (i < b)
		pthread_join(threads[i++], NULL);
	i = 0;
	while (i < (b + 2))
	{
		if (pthread_mutex_destroy(&philo->philo->mutex_array[i]) != 0)
			printf("Failed to destroy mutex_array [%d] mutex\n", i);
		i++;
	}
	free(threads);
	free(philo->philo->mutex_array);
	free(philo->philo);
}
