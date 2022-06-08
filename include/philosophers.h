/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:17:30 by fcassand          #+#    #+#             */
/*   Updated: 2022/05/21 03:09:18 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_forks
{
	pthread_mutex_t	*fork;
}	t_forks;

typedef struct s_print
{
	pthread_mutex_t	m_print;
}	t_print;

typedef struct	s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				times_eat;
	int				eat_time;
	int				eat_time;
	int				die_time;
	int				sleep_time;
	long long		last_eat;
	long long		death_time;
	long long		start;
	t_forks			*forks;
	t_print			*print;
	struct t_all	*info;
}				t_philo;

typedef struct	s_all
{
	int				amount;
	int				eat_time;
	int				die_time;
	int				sleep_time;
	pthread_t 		*tred;
	int				times_must_eat;
	long long		start;
	t_philo			*philo;
	t_forks			*forks;
	t_print			*print;
}				t_all;

int	main(int argc, char **argv);
int	ft_atoi(const char *str);

#endif
