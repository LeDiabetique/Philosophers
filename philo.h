/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:15:41 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/24 09:44:42 by hdiot            ###   ########.fr       */
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
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_die;
	int			nbr_philo;
	int			loop;
	long int	actual_time;
}	t_info;

typedef struct s_philo
{
	int				left_fork;
	int				right_fork;
	int				max_eat;
	int				speak;
	long int		start_timer;
	int				dead;
	int				is_dead;
	int				rule;
	pthread_mutex_t	*mutex_array;
	int				mutex_eat;
	t_info			info_philo;
	long int		timer;
	long int		last_eat;
	int				current_loop;
	int				id;
}	t_philo;

typedef struct s_ph
{
	t_philo	*philo;
	t_info	info;
}	t_ph;

int			check_max_int(char *str);
int			check_value(t_ph *philo);
int			check_digits(char **av);
int			bad_args_message(void);
int			init_rules(t_ph *philo, char **av);

void		ft_putstr_fd(char *str, int fd);
int			ft_atoi(const char	*str);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *c);

long int	timestamp(void);
int			eating(t_philo *philo);
int			sleep_think(t_philo *philo);
long int	ft_usleep(int tlimit);
void		*get_time(void *info);
void		init_mutex(t_ph *philo);
void		destroy_philo(t_ph *philo, pthread_t *threads);
long int	timestamp_diff(long int start);
int			is_dead(t_ph *philo, int i);
void		set_rule_to_one(t_ph *philo);
void		speaking(t_philo *philo, char *str);

#endif
