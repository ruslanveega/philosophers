/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 03:14:55 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/21 01:54:12 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	kill_process(t_all *info)
{
	int	i;

	i = 0;
	while (i < info->amount)
		if (info->pid[i])
			kill(info->pid[i++], SIGKILL);
	return (0);
}

void	free_info(t_all *info)
{
	if (info)
	{
		if (info->philo)
			free(info->philo);
		if (info->pid)
			free(info->pid);
		free(info);
	}
	info = NULL;
}

int	error_massage(char *str, t_all *info)
{
	printf("ERROR: %s\n", str);
	if (info)
		free_info(info);
	return (1);
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
