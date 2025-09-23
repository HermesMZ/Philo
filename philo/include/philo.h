/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:24:52 by zoum              #+#    #+#             */
/*   Updated: 2025/09/18 14:02:35 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <x86_64-linux-gnu/bits/pthreadtypes.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	long			start_time;
	int				dead;
	int				all_ate;
	int				eating_count;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	eating_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long			last_meal_time;
	t_data			*data;
	pthread_t		thread;
	pthread_t		monitor_thread;
}	t_philo;

// checks.c
int		should_stop(t_philo *philo);
int		check_death(t_philo *philo);
void	*monitor_stop(void *arg);

// forks.c
void	release_forks(t_philo *philo);
void	set_fork_order(t_philo *philo, int *first_fork, int *second_fork);
int		take_forks(t_philo *philo, int first_fork, int second_fork);
void	print_fork_taken(t_philo *philo);

// init.c
t_data	*init_philos_and_mutex(t_data *data);
t_data	*init_data(int argc, char **argv);

// routine .c
int		philo_sleeping(t_philo *philo);
int		philo_thinking(t_philo *philo);
int		philo_eating(t_philo *philo);
void	*single_philo_routine(t_philo *philo);
void	*routine(void *arg);

// utils.c
void	safe_print(t_philo *philo, const char *message);
long	get_time_in_ms(void);
void	clean_all(t_data *data);
void	*start_simulation(t_data *data);

// lib
int		ft_atoi(const char *str);
long	ft_atol(const char *str);

#endif /* PHILO_H */