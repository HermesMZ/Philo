/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:24:52 by zoum              #+#    #+#             */
/*   Updated: 2025/09/05 01:56:51 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	int				time_to_think;
	int				num_meals;
	long			start_time;
	int				all_ate;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
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
}	t_philo;

// philo
void	clean_all(t_data *data);
void	*start_simulation(t_data *data);

// routine
void	routine(void *arg);
int		philo_sleeping(t_philo *philo);
int		philo_thinking(t_philo *philo);
int		philo_eating(t_philo *philo);
void	take_right_fork(t_philo *philo);
void	take_left_fork(t_philo *philo);
void	release_forks(t_philo *philo);

// lib
int		ft_atoi(const char *str);


#endif /* PHILO_H */