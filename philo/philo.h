/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:15:41 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/21 18:44:22 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_info
{
	int			teat;
	int			tsleep;
	int			tdie;
	int			nbr_philo;
	int			loop;
	long int	acttime;
}	t_info;

typedef struct s_philo
{
	int				l_fork;
	int				r_fork;
	int				maxeat;
	int				speak;
	long int		stimer;
	pthread_mutex_t	*fork;
	int				meat;
	t_info			infph;
	long int		timer;
	long int		lasteat;
	int				curloop;
	int				id;
}	t_philo;

typedef struct s_ph
{
	t_philo	*ph;
	t_info	info;
}	t_ph;

void		checkmaxint(char *str);
void		checkvalue(t_ph *ph);
void		checkdigits(char **av);
int			nbrargs(void);
void		getinfo(t_ph *ph, char **av);

void		ft_putstr_fd(char *str, int fd);
int			ft_atoi(const char	*str);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *c);

long int	timestamp(void);
void		eating(t_philo *ph);
void		sleepthink(t_philo *ph);
long int	ft_usleep(int tlimit);
void		*get_time(void *info);
void		init_mutex(t_ph *ph);
void		destroy_philo(t_ph *ph, pthread_t *threads);
long int	timestampdiff(long int start);
int			is_dead(t_ph *ph, int i);

#endif
