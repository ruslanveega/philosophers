/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 03:14:55 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/15 02:39:19 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_destroy(t_all *info)
{
	int	i;

	i = -1;
	while (++i < info->amount)
		if (pthread_mutex_destroy(&info->forks->fork[i]))
			printf("Error destroy mutex %d.\n", i);
	pthread_mutex_destroy(&info->m_print);
	pthread_mutex_destroy(&info->check_mut);
	pthread_mutex_destroy(&info->check_meals);
}

void	free_info(t_all *info)
{
	if (info->philo)
		free(info->philo);
	if (info->forks)
	{
		if (info->forks->fork)
			free(info->forks->fork);
		free(info->forks);
	}
	if (info->tred)
		free(info->tred);
	if (info)
		free(info);
}

int	error_massage(char *str, t_all *info)
{
	printf("ERROR: %s\n", str);
	if (info)
		free_info(info);
	return (1);
}

long long	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while ((*str != '\0' && *str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = 10 * num + (*str - '0');
		str++;
	}
	return (num * sign);
}
