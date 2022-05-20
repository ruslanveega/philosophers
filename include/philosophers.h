/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:17:30 by fcassand          #+#    #+#             */
/*   Updated: 2022/05/20 03:56:20 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int	id;
	int	left_fork;
	int	right_fork;
	int	times_eat;
}				t_philo;

typedef struct	s_all
{
	int				amount;
	int				eat_time;
	int				die_time;
	int				sleep_time;
	pthread_t 		*tred;
	pthread_mutex_t *fork;
	t_philo 		*philo;
}				t_all;

int	main(int argc, char **argv);
int	ft_atoi(const char *str);

#endif
