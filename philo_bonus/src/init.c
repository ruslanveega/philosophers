/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 04:15:57 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/22 00:20:17 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	make_arr_and_sem(t_all *info)
{
	int	id;

	id = 0;
	info->pid = malloc(sizeof(pid_t) * info->amount);
	if (!info->pid)
		return (error_massage("allocation error", info));
	while (id < info->amount)
		info->pid[id++] = 0;
	sem_unlink(FORKS);
	sem_unlink(PWE);
	sem_unlink(PRINT);
	info->forks = sem_open(FORKS, O_CREAT, 0644, info->amount);
	if (info->forks == SEM_FAILED)
		return (error_massage("sem_failed error", info));
	info->pwe = sem_open(PWE, O_CREAT, 0644, 1);
	if (info->pwe == SEM_FAILED)
		return (error_massage("sem_failed error", info));
	info->print = sem_open(PRINT, O_CREAT, 0644, 1);
	if (info->print == SEM_FAILED)
		return (error_massage("sem_failed error", info));
	return (0);
}

int	init_philo(t_all *info)
{
	info->philo = malloc(sizeof(t_philo));
	if (!info->philo)
		return (error_massage("allocation error", info));
	info->philo->id = 0;
	info->philo->times_eat = 0;
	info->philo->death_time = info->die_time + info->start;
	return (0);
}

int	init_info(t_all *info, char **av, int argc)
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || \
	ft_atoi(av[4]) <= 0)
		return (error_massage("wrong arguments format", info));
	info->amount = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (argc == 6)
		info->times_must_eat = ft_atoi(av[5]);
	else
		info->times_must_eat = 0;
	info->forks = NULL;
	info->philo = NULL;
	info->print = NULL;
	info->pid = NULL;
	info->pwe = NULL;
	info->start = get_timestamp();
	if (init_philo(info))
		return (1);
	if (make_arr_and_sem(info))
		return (1);
	return (0);
}
