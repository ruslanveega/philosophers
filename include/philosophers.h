/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:17:30 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/12 22:25:18 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_forks
{
	pthread_mutex_t	*fork;
}			t_forks;

typedef struct	s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				times_eat;
	int				eat_time;
	int				die_time;
	int				sleep_time;
	int				times_must_eat;
	long long		last_eat;
	long long		death_time;
	long long		start;
	struct s_all	*info;
	t_forks			*forks;
	pthread_mutex_t	m_print;
}				t_philo;

typedef struct	s_all
{
	int				amount;
	int				eat_time;
	int				die_time;
	int				sleep_time;
	int				times_must_eat;
	int				stop_flag;
	int				philos_were_eat;
	long long		start;
	t_philo			*philo;
	pthread_t 		*tred;
	t_philo 		*philo;
	t_forks			*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	check_mut;
	pthread_mutex_t	check_meals;
 }				t_all;

int			main(int argc, char **argv);
int			ft_atoi(const char *str);
int			print_func(t_all *info, t_philo *philo, char *str);
int			check_death(void *info);
static int	start(t_all *info);
void		philo_life(void *tmp);
int			ruitine(t_all *info, t_philo *philo);
int			init_info(t_all *info, char **av, int argc);
int			init_mutex(t_all *info);
void		init_philo(t_all *info);
long long	get_timestamp(void);
int			error_massage(char *str, t_all *info);
int			philo_is_eating(t_all *info, t_philo *philo);
int			one_more_philos(t_all *info);
int			one_more_philos(t_all *info);
int			philos_time(long long time, t_all *info);
#endif
