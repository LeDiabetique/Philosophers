/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:14:06 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/24 10:02:56 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_over(t_ph *philo)
{
	int	i;
	int	b;
	int	onedied;

	onedied = 0;
	while (!(philo->philo->rule))
	{
		i = -1;
		while (++i < philo->philo->info_philo.nbr_philo && !philo->philo[i].is_dead)
		{
			if (!onedied && is_dead(philo, i) == 1)
				return (onedied = 1, 1);
		}
		pthread_mutex_lock(&philo->philo[0].mutex_array[philo->philo[0].mutex_eat]);
		b = 0;
		while (b < philo->philo[0].info_philo.nbr_philo \
			&& philo->philo[0].max_eat >= philo->philo[0].info_philo.loop)
			b++;
		pthread_mutex_unlock(&philo->philo[0].mutex_array[philo->philo[0].mutex_eat]);
		if (b == philo->philo[0].info_philo.nbr_philo)
			philo->philo->rule = 1;
	}
	return (1);
}

int	is_dead(t_ph *philo, int i)
{
	long int	time;
	int			time_to_die;

	time_to_die = philo->philo[i].info_philo.time_to_die;
	time = timestamp();
	pthread_mutex_lock(&philo->philo[i].mutex_array[philo->philo[i].mutex_eat]);
	if (time - philo->philo[i].last_eat >= time_to_die && philo->philo[i].rule != 1)
	{
		pthread_mutex_lock(&philo->philo[i].mutex_array[philo->philo->speak]);
		printf("%ld [%d] \033[91mdied\033[0m\n", \
			time - philo->philo[i].start_timer, philo->philo[i].id);
		set_rule_to_one(philo);
		pthread_mutex_unlock(&philo->philo[i].mutex_array[philo->philo->speak]);
		return (pthread_mutex_unlock(&philo->philo[i].mutex_array[philo->philo[i].mutex_eat]), 1);
	}
	pthread_mutex_unlock(&philo->philo[i].mutex_array[philo->philo->mutex_eat]);
	usleep(100);
	return (0);
}

void	set_rule_to_one(t_ph *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo->info_philo.nbr_philo)
	{
		philo->philo[i].is_dead = 1;
		i++;
	}
}

int	philo(char **av)
{
	t_ph		philo;
	int			i;
	pthread_t	*threads;

	i = 0;
	if (init_rules(&philo, av) == 1)
		return (1);
	threads = malloc(sizeof(pthread_t) * philo.philo->info_philo.nbr_philo);
	if (!threads)
		return (free(philo.philo), 1);
	init_mutex(&philo);
	while (i < philo.philo->info_philo.nbr_philo)
	{
		pthread_create(&threads[i], NULL, get_time, &philo.philo[i]);
		i++;
	}
	is_over(&philo);
	ft_usleep((philo.philo->info_philo.time_to_die + philo.philo->info_philo.time_to_eat \
		+ philo.philo->info_philo.time_to_sleep) * 2);
	destroy_philo(&philo, threads);
	return (0);
}

int	main(int argc, char **argv)
{
	(void) argc;
	if (argc < 5 || argc > 6)
		return (bad_args_message());
	if (philo(argv) == 1)
		return (1);
	return (0);
}
