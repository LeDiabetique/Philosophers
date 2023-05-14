/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:14:06 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/10 15:41:56 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int nbrargs(void)
{
	printf("Must have those arguments :\n");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep\n");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	return (1);
}

void	getinfo(t_ph *ph, char **av)
{
	int i;

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

void	*test(void *info)
{
	t_philo *ph;

	ph = (t_philo *)info;
	newtime(ph);
	
	return (info);
}

void	philo(char **av)
{
	t_ph ph;
	int i;

	i = 0;
	getinfo(&ph, av);
	while (i < ph.ph->infph.nbr_philo)
	{
		pthread_create(&ph.ph[i].thread_id, NULL, test, &ph.ph[i]);
		pthread_join(ph.ph[i].thread_id, NULL);
		i++;
	}
		free(ph.ph);
}

int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return(nbrargs());
	philo(argv);
	return (0);
}