/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 03:18:27 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/11 04:51:41 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_func(t_all *info, t_philo *philo, char *str)
{
	prhread_mutex_lock(&info->check_mut);
	prhread_mutex_lock(&info->print->m_print);
	if (!info->is_dead)
	{
		prhread_mutex_unlock(&info->check_mut);
		printf("%7lldms %d is %s\n", get_timestamp() - philo->start,
		philo->id, str);
		prhread_mutex_unlock(&info->print->m_print);
		return (0);
	}
	prhread_mutex_unlock(&info->check_mut);
	prhread_mutex_unlock(&info->print->m_print);
	return (1);
}

int	check_death(void *info)
{

}

int	philo_life(void *tmp)
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

	}

}

static int	start(t_all *info)
{
	int	id;
	pthread_t	death;

	id = -1;
	while (++id < info->amount)
		pthread_create(&info->tred[id], NULL, &philo_life, &info->philo[id]);
	pthread_create(&death, NULL, check_death, info);
	pthread_join(death, NULL);
	id = -1;
	pthread_mutex_unlock(&info->print->m_print);
	while (++id < info->amount)
		pthread_join(info->tred[id], NULL);
	return (0);
}
