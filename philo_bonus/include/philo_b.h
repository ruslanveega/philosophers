/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:17:30 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/18 04:29:06 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_B_H
# define PHILO_B_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <pthread.h>
# include <sys/time.h>

# define FORKS "forks"
# define PRINT "print"
# define PWE "philos_were_eat"

typedef struct s_philo
{
	int				id;
	int				times_eat;
	long long		last_eat;
	long long		death_time;
}				t_philo;

typedef struct s_all
{
	int				amount;
	int				eat_time;
	int				die_time;
	int				sleep_time;
	int				times_must_eat;
	long long		start;
	t_philo			*philo;
	sem_t			*print;
	sem_t			*pwe;
	sem_t			*forks;
	pid_t			*pid;
}				t_all;

int			main(int argc, char **argv);
int			ft_atoi(const char *str);
int			init_info(t_all *info, char **av, int argc);
int			init_philo(t_all *info);
long long	get_timestamp(void);
void		free_info(t_all *info);
int			start(t_all *info, t_philo *philo);
void		*is_philo_dead(void *tmp);
void		print_func(t_philo *philo, t_all *info, char *action);
void		*check_meals(void *tmp);
int			error_massage(char *str, t_all *info);
void		philos_time(long long time);
int			kill_process(t_all *info);
#endif
