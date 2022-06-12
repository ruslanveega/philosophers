/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:46:59 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/12 18:42:38 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(void *tmp)
{
	t_all	*info;
	t_philo	*philo;

	info = (t_all *)tmp;
	philo = info->philo;


}

int	print_func(t_all *info, t_philo *philo, char *str)
{
	prhread_mutex_lock(&info->check_mut);
	prhread_mutex_lock(&info->m_print);
	if (!info->stop_flag)
	{
		prhread_mutex_unlock(&info->check_mut);
		printf("%7lldms %d is %s\n", get_timestamp() - philo->start,
		philo->id, str);
		prhread_mutex_unlock(&info->m_print);
		return (0);
	}
	prhread_mutex_unlock(&info->check_mut);
	prhread_mutex_unlock(&info->m_print);
	return (1);
}

int	one_more_philos(t_all *info)
{
	pthread_mutex_lock(&info->check_meals);
	info->philos_were_eat++;
		if (info->philos_were_eat == info->amount)
		{
			pthread_mutex_lock(&info->check_mut);
			info->stop_flag = 1;
			pthread_mutex_unlock(&info->check_mut);
			pthread_mutex_unlock(&info->check_meals);
			return (1);
		}
	pthread_mutex_unlock(&info->check_meals);
	return (0);
}

int	philos_time(long long time, t_all *info)
{
	long long	stop;

	stop = get_timestamp() + time;
	while (get_timestamp() < stop)
	{
		pthread_mutex_lock(&info->check_mut);
		if (info->stop_flag)
		{
			pthread_mutex_unlock(&info->check_mut);
			return (1);
		}
		pthread_mutex_unlock(&info->check_mut);
		usleep(500);
	}
	return (0);
}

static int	unlock_forks(t_all *info, t_philo *philo, int num)
{
	if (num == 2)
		pthread_mutex_unlock(&info->forks->fork[philo->left_fork]);
	pthread_mutex_unlock(&info->forks->fork[philo->right_fork]);
	return (1);
}
