/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:30:04 by zoum              #+#    #+#             */
/*   Updated: 2025/09/09 17:20:37 by mzimeris         ###   ########.fr       */
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
		if (stop_check(philo) || death_check(philo))
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
	while (!stop_check(philo) && !death_check(philo))
	{
		usleep(50);
		break ;
	}
	return (stop_check(philo) || death_check(philo));
}

int	philo_eating(t_philo *philo)
{
	long	start_time;

	start_time = get_time_in_ms();
	philo->last_meal_time = start_time;
	safe_print(philo, "is eating");
	while (get_time_in_ms() - start_time < philo->data->time_to_eat)
	{
		if (stop_check(philo) || death_check(philo))
			return (release_forks(philo), 1);
		usleep(10);
	}
	release_forks(philo);
	philo->meals_eaten++;
	if (philo->data->num_meals != -1
		&& philo->meals_eaten == philo->data->num_meals)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		philo->data->all_ate++;
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
	return (0);
}

void	*single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[0]);
	safe_print(philo, "has taken a fork");
	while (!death_check(philo))
		usleep(10);
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
	while (!stop_check(philo) && !death_check(philo))
	{
		if (take_forks(philo, first_fork, second_fork) == 1)
			break ;
		print_fork_taken(philo);
		if (philo_eating(philo) == 1)
			break ;
		if (stop_check(philo) || death_check(philo))
			break ;
		if (philo_sleeping(philo) == 1)
			break ;
		if (philo_thinking(philo) == 1)
			break ;
	}
	return (NULL);
}
