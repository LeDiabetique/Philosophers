/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:20:32 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/04 09:24:28 by hdiot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char	*str)
{
	char	*s;
	int		sign;
	int		res;

	s = (char *)str;
	sign = 1;
	res = 0;
	while (*s == 32 || *s == '\f' || *s == '\n'
		|| *s == '\r' || *s == '\t' || *s == '\v')
			s++;
	if (*s == '-')
	{
		sign = sign * -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + *s - '0';
		if (!(*s >= '0' && *s <= '9'))
			return (res * sign);
		s++;
	}
	return (res * sign);
}
