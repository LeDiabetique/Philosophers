/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:24:24 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/10 10:43:28 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void newtime(t_philo *ph)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    ph->infph.acttime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    printf("time is %d\n", (int)ph->infph.acttime);
}