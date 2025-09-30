/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:30:04 by zoum              #+#    #+#             */
/*   Updated: 2025/09/30 14:20:51 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleeping(t_philo *philo)
{
	long	start_time;

	start_time = get_time_in_ms();
	pthread_mutex_lock(&philo->data->data_mutex);
	if (!philo->data->dead)
		safe_print(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->data_mutex);
	while (get_time_in_ms() - start_time < philo->data->time_to_sleep)
	{
		if (should_stop(philo))
			return (1);
		usleep(10);
	}
	return (0);
}

int	philo_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (!philo->data->dead)
		safe_print(philo, "is thinking");
	pthread_mutex_unlock(&philo->data->data_mutex);
	while (!should_stop(philo))
	{
		usleep(50);
		break ;
	}
	return (should_stop(philo));
}

int	philo_eating(t_philo *philo)
{
	long	start_time;

	start_time = get_time_in_ms();
	pthread_mutex_lock(&philo->data->eating_mutex);
	philo->last_meal_time = start_time;
	pthread_mutex_unlock(&philo->data->eating_mutex);
	safe_print(philo, "is eating");
	while (get_time_in_ms() - start_time < philo->data->time_to_eat)
	{
		if (should_stop(philo))
			return (release_forks(philo), 1);
		usleep(10);
	}
	release_forks(philo);
	pthread_mutex_lock(&philo->data->eating_mutex);
	philo->meals_eaten++;
	if (philo->data->num_meals != -1
		&& philo->meals_eaten == philo->data->num_meals)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		philo->data->all_ate++;
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
	pthread_mutex_unlock(&philo->data->eating_mutex);
	return (0);
}

void	*single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[0]);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%13ld %3d has taken a fork\n", get_time_in_ms()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(&philo->data->forks[0]);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		first_fork;
	int		second_fork;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
		return (single_philo_routine(philo));
	set_fork_order(philo, &first_fork, &second_fork);
	if (philo->id % 2 == 0)
		usleep(100);
	while (!should_stop(philo))
	{
		if (take_forks(philo, first_fork, second_fork) == 1)
			break ;
		print_fork_taken(philo);
		if (philo_eating(philo) == 1)
			break ;
		if (should_stop(philo))
			break ;
		if (philo_sleeping(philo) == 1)
			break ;
		if (philo_thinking(philo) == 1)
			break ;
	}
	return (NULL);
}
