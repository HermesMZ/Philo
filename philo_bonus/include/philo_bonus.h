/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:57:13 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/15 12:49:24 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	struct s_philo	*philos;
	sem_t			*forks;
	sem_t			*writing;
	sem_t			*stop;
	sem_t			*meals_done;
	long			start_time;
	pid_t			*pid;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	int				should_stop;
	t_data			*data;
}	t_philo;

// checks_bonus.c
int		death_check(t_philo *philo);
int		stop_check(t_philo *philo);

// forks_bonus.c
int		take_forks(t_philo *philo);
int		philo_eating(t_philo *philo);
void	*single_philo_routine(t_philo *philo);

// init_bonus.c
t_data	*init_philos_and_semaphore(t_data *data);
t_data	*init_data(int argc, char **argv);

// routine_bonus.c
int		philo_sleeping(t_philo *philo);
int		philo_thinking(t_philo *philo);
void	*philo_routine(t_philo *philo);

// simulation_bonus.c
void	*monitor_stop(void *arg);
void	*monitor_meals(void *arg);
void	start_philo(t_philo *philo);
void	start_simulation(t_data *data);

// utils.c
long	get_time_in_ms(void);
void	safe_print(t_philo *philo, const char *message);
void	clean_semaphores(t_data *data);
void	cleanup(t_data *data);
void	final_cleanup(t_data *data);

// lib
int		ft_atoi(const char *str);
long	ft_atol(const char *str);

#endif