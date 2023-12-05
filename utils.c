/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:20:32 by hdiot             #+#    #+#             */
/*   Updated: 2023/05/15 14:39:50 by hdiot            ###   ########.fr       */
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

int	ft_atoi(const char	*param_str)
{
	char	*string;
	int		sign;
	int		result;

	string = (char *)param_str;
	sign = 1;
	result = 0;
	while (*string == 32 || *string == '\f' || *string == '\n'
		|| *string == '\r' || *string == '\t' || *string == '\v')
		string++;
	if (*string == '-')
	{
		sign = sign * -1;
		string++;
	}
	else if (*string == '+')
		string++;
	while (*string >= '0' && *string <= '9')
	{
		result = result * 10 + *string - '0';
		if (!(*string >= '0' && *string <= '9'))
			return (result * sign);
		string++;
	}
	return (result * sign);
}

int	bad_args_message(void)
{
	printf("Must have those arguments :\n");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep\n");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	return (1);
}
