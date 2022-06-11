/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 04:15:57 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/11 04:41:33 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_philo(t_all *info)
{
	int	i;

	i = 0;
	while (i < info->amount)
	{
		info->philo[i].id = i + 1;
		info->philo[i].times_eat = 0;
		info->philo[i].last_eat = info->start;
		info->philo[i].right_fork = i;
		info->philo[i].left_fork = 0;
		if (i < info->amount - 1)
			info->philo[i].left_fork = i + 1;
		info->philo[i].eat_time = info->eat_time;
		info->philo[i].die_time = info->die_time;
		info->philo[i].sleep_time = info->sleep_time;
		info->philo[i].start = info->start;
		info->philo[i].print = info->print;
		info->philo[i].forks = info->forks;
		info->philo[i].info = info;
		i++;
	}
}

int	init_mutex(t_all *info)
{
	t_forks *forks;
	int		i;

	info->forks = malloc(sizeof(t_forks));
	info->print = malloc(sizeof(t_print));
	info->philo = malloc(sizeof(t_philo) * info->amount);
	info->tred = malloc(sizeof(pthread_t) * info->amount);
	i = 0;
	if (info->forks && info->print && info->philo && info->tred)
	{
		forks->fork = malloc(sizeof(pthread_mutex_t) * info->amount);
		if (!forks)
			return (error_message("allocation error", info));
		info->forks = forks;
		while (i < info->amount)
			if(pthread_mutex_init(&info->forks->fork[i++], NULL))
				return (1);
		if(pthread_mutex_init(&info->print->m_print, NULL))
				return (1);
		if (pthread_mutex_init(&info->check_mut, NULL))
			return (1);
		return (0);
	}
	return (error_message("allocation error", info));
}

int	init_info(t_all *info, char **av, int argc)
{
	if (argc != 5 || argc != 6)
 		return(error_message("wrong number of arguments", info));
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 ||
		ft_atoi(av[4]) <= 0)
		return (error_message("wrong arguments format", info));
	info->amount = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (argc == 6)
		info->times_must_eat = ft_atoi(av[5]);
	info->is_dead = 0;
	info->forks = NULL;
	info->philo = NULL;
	info->tred = NULL;
	info->print = NULL;
	info->start = get_timestamp();
	if (init_mutex(info))
		return (1);
	init_philo(info);
	return (0);
}


