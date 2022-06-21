/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 03:18:27 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/16 03:00:05 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_philo_dead(t_all *info, t_philo *philo)
{
	long long	time_stamp;

	time_stamp = get_timestamp() - philo->start;
	pthread_mutex_lock(&philo->death_mut);
	if (philo->death_time < time_stamp)
	{
		pthread_mutex_unlock(&philo->death_mut);
		pthread_mutex_lock(&info->check_mut);
		info->stop_flag = 1;
		pthread_mutex_unlock(&info->check_mut);
		pthread_mutex_lock(&info->m_print);
		printf("%7lldms philosopher is %d died\n", \
		time_stamp, philo->id);
		return (1);
	}
	pthread_mutex_unlock(&philo->death_mut);
	pthread_mutex_lock(&info->check_mut);
	if (info->stop_flag)
	{
		pthread_mutex_unlock(&info->check_mut);
		return (1);
	}
	pthread_mutex_unlock(&info->check_mut);
	return (0);
}

int	philo_is_eating(t_all *info, t_philo *philo)
{
	pthread_mutex_lock(&info->forks->fork[philo->right_fork]);
	if (print_func(info, philo, "taken a fork"))
		return (unlock_forks(info, philo, 1));
	pthread_mutex_lock(&info->forks->fork[philo->left_fork]);
	if (print_func(info, philo, "taken a fork"))
		return (unlock_forks(info, philo, 2));
	if (is_philo_dead(info, philo))
		return (unlock_forks(info, philo, 2));
	if (print_func(info, philo, "eating"))
		return (unlock_forks(info, philo, 2));
	if (philos_time(philo->eat_time, info))
		return (unlock_forks(info, philo, 2));
	pthread_mutex_lock(&philo->death_mut);
	philo->death_time = get_timestamp() - philo->start + philo->die_time;
	pthread_mutex_unlock(&philo->death_mut);
	unlock_forks(info, philo, 2);
	if (info->times_must_eat)
	{
		philo->times_must_eat--;
		if (!philo->times_must_eat)
			return (one_more_philos(info));
	}
	return (0);
}

int	ruitine(t_all *info, t_philo *philo)
{
	pthread_mutex_lock(&info->check_mut);
	if (info->stop_flag)
	{
		pthread_mutex_unlock(&info->check_mut);
		return (0);
	}
	pthread_mutex_unlock(&info->check_mut);
	if (philo_is_eating(info, philo))
		return (1);
	if (print_func(info, philo, "sleeping"))
		return (1);
	if (philos_time(philo->sleep_time, info))
		return (1);
	if (print_func(info, philo, "thinking"))
		return (1);
	return (0);
}

void	*philo_life(void *tmp)
{
	t_philo	*philo;
	t_all	*info;

	philo = (t_philo *)tmp;
	info = philo->info;
	if (philo->id % 2 != 0)
	{
		print_func(info, philo, "thinking");
		usleep(philo->eat_time * 990 - 1);
	}
	while (1)
	{
		pthread_mutex_lock(&info->check_mut);
		if (info->stop_flag)
		{
			pthread_mutex_unlock(&info->check_mut);
			return (NULL);
		}
		pthread_mutex_unlock(&info->check_mut);
		if (ruitine(info, philo))
			return (NULL);
	}
	return (NULL);
}

int	start(t_all *info)
{
	int			id;
	pthread_t	death;

	id = -1;
	while (++id < info->amount)
		pthread_create(&info->tred[id], NULL, &philo_life, &info->philo[id]);
	pthread_create(&death, NULL, &check_death, info);
	pthread_join(death, NULL);
	if (info->amount == 1)
		pthread_mutex_unlock(&info->forks->fork[info->philo[0].right_fork]);
	pthread_mutex_unlock(&info->m_print);
	id = -1;
	while (++id < info->amount)
		pthread_join(info->tred[id], NULL);
	return (0);
}
