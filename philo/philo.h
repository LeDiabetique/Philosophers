/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:15:41 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/16 16:26:55 by hdiot            ###   ########.fr       */
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
	pthread_mutex_t	speak;
	pthread_mutex_t	*fork;
	t_info			infph;
	long int		timer;
	long int		start_time;
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

void		ft_putstr_fd(char *str, int fd);
int			ft_atoi(const char	*str);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *c);

long int	timestamp(void);
void		eating(t_philo *ph);
void		sleepthink(t_philo *ph);
long int	ft_usleep(int tlimit);

#endif