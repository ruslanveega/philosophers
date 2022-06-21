/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 03:18:27 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/22 00:24:40 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	ruitine(t_all *info, t_philo *philo)
{
	long long	time;

	time = get_timestamp();
	if (time > philo->death_time)
		exit(1);
	sem_wait(info->forks);
	print_func(philo, info, "take fork");
	sem_wait(info->forks);
	print_func(philo, info, "take fork");
	print_func(philo, info, "is eating");
	philo->times_eat++;
	philo->death_time = get_timestamp() + info->die_time;
	philos_time(info->eat_time);
	sem_post(info->forks);
	sem_post(info->forks);
	if (info->times_must_eat && \
	info->times_must_eat == philo->times_eat)
		sem_post(info->pwe);
	print_func(philo, info, "is sleeping");
	philos_time(info->eat_time);
	print_func(philo, info, "is thinking");
}

int	new_philo(t_all *info, t_philo *philo)
{
	pthread_t	death;
	pthread_t	meals;

	if (pthread_create(&death, NULL, &is_philo_dead, info))
		return (1);
	if (info->times_must_eat && philo->id == 1)
		if (pthread_create(&meals, NULL, &check_meals, info))
			return (1);
	if (philo->id % 2 != 0)
	{
		print_func(philo, info, "is thinking");
		usleep(500);
	}
	while (1)
		ruitine(info, philo);
	if (pthread_join(death, NULL))
		return (1);
	if (pthread_join(meals, NULL))
		return (1);
	return (0);
}

int	start(t_all *info, t_philo *philo)
{
	int	i;
	int	status;

	i = 0;
	info->start = get_timestamp();
	philo->last_eat = info->start;
	while (i < info->amount)
	{
		philo->id = i + 1;
		info->pid[i] = fork();
		if (info->pid[i] == -1)
			kill_process(info);
		if (info->pid[i] == 0)
			if (new_philo(info, philo))
				kill_process(info);
		usleep (10);
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
			kill_process(info);
	}
	return (0);
}
