/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 03:18:27 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/12 22:23:07 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_philo_dead(long long c_time, t_all *info, t_philo *philo)
{
	if (philo->die_time < time - philo->start)
}

int	philo_is_eating(t_all *info, t_philo *philo)
{
	long long	time_stamp;

	pthread_mutex_lock(&info->forks->fork[philo->right_fork]);
	if (print_func(info, philo, "taken a fork"))
		return (unlock_forks(info, philo, 1));
	pthread_mutex_lock(&info->forks->fork[philo->left_fork]);
	if (print_func(info, philo, "taken a fork"))
		return (unlock_forks(info, philo, 2));
	time_stamp = get_timestamp() - philo->start;
	if (is_philo_dead(time_stamp, info, philo))
		return (unlock_forks(info, philo, 2));
	if (print_func(info, philo, "eating"))
		return (unlock_forks(info, philo, 2));
	if (philos_time(philo->eat_time, info))
		return (unlock_forks(info, philo, 2));
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
	prhread_mutex_lock(&info->check_mut);
	if (info->stop_flag)
	{
		prhread_mutex_unlock(&info->check_mut);
		return (0);
	}
	prhread_mutex_unlock(&info->check_mut);
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

void	philo_life(void *tmp)
{
	t_philo	*philo;
	t_all	*info;

	philo = (t_philo *)tmp;
	info = philo->info;
	if (philo->id % 2 != 0)
	{
		print_func(info, philo, "thinking");
		usleep(50);
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

static int	start(t_all *info)
{
	int			id;
	pthread_t	death;

	id = -1;
	while (++id < info->amount)
		pthread_create(&info->tred[id], NULL, &philo_life, &info->philo[id]);
	pthread_create(&death, NULL, check_death, info);
	pthread_join(death, NULL);
	id = -1;
	pthread_mutex_unlock(&info->m_print);
	while (++id < info->amount)
		pthread_join(info->tred[id], NULL);
	return (0);
}
