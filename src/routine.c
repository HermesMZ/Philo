/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:30:04 by zoum              #+#    #+#             */
/*   Updated: 2025/09/05 02:00:18 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("Philosopher %d is sleeping\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_sleep * 1000);
	return (0);
}

int	philo_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("Philosopher %d is thinking\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

int	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("Philosopher %d is eating\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_eat * 1000);
	release_forks(philo);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	return (0);
}

void	routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	take_right_fork(philo);
	take_left_fork(philo);
	philo_eating(philo);
	release_forks(philo);
	philo_sleeping(philo);
	philo_thinking(philo);
}
