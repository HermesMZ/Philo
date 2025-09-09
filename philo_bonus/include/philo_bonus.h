/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:57:13 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/09 18:51:39 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Voici une pratique recommandée :

// Parent :

// sem_open(...)

// fork()

// Dans le parent : attendre que les enfants terminent.

// sem_close(...)

// sem_unlink(...) (si c’est le dernier utilisateur)

// Enfant(s) :

// Le descripteur sem_t * est hérité via le fork, donc
// inutile de refaire sem_open.

// À la fin : faire sem_close(...) (pas sem_unlink !)

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
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
	long			start_time;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	t_data			*data;
}	t_philo;

// init_bonus.c
t_data	*init_philos_and_semaphore(t_data *data);
t_data	*init_data(int argc, char **argv);

// routine_bonus.c
void	release_forks(t_philo *philo);
int		take_forks(t_philo *philo);
void	print_fork_taken(t_philo *philo);
int		philo_sleeping(t_philo *philo);
int		philo_thinking(t_philo *philo);
int		philo_eating(t_philo *philo);
void	*single_philo_routine(t_philo *philo);
void	*philo_routine(t_philo *philo);

// checks_bonus.c
int		death_check(t_philo *philo);
int		stop_check(t_philo *philo);

// utils.c
long	get_time_in_ms(void);
void	cleanup(t_data *data);

// lib
int		ft_atoi(const char *str);
long	ft_atol(const char *str);

#endif