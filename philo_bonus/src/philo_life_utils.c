/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:46:59 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/22 00:21:32 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	*check_meals(void *tmp)
{
	t_all	*info;
	int		i;

	info = (t_all *)tmp;
	i = 0;
	sem_wait(info->pwe);
	while (i++ < info->amount)
		sem_wait(info->pwe);
	sem_wait(info->print);
	exit(1);
	return (NULL);
}

void	*is_philo_dead(void *tmp)
{
	t_all	*info;
	t_philo	*philo;

	info = (t_all *)tmp;
	philo = info->philo;
	while (1)
	{
		if (get_timestamp() > philo->death_time)
		{
			sem_wait(info->print);
			printf("%7lldms philosopher %d is died\n", \
			get_timestamp() - info->start, philo->id);
			exit (1);
		}
	}
}

void	philos_time(long long time)
{
	long long	start;

	start = get_timestamp();
	while (get_timestamp() - start < time)
		usleep(100);
}

void	print_func(t_philo *philo, t_all *info, char *action)
{
	sem_wait(info->print);
	printf("%7lldms philosopher %d is %s\n", \
	get_timestamp() - info->start, philo->id, action);
	sem_post(info->print);
}

long long	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
