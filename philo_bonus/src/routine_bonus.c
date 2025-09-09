/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:13:05 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/09 18:44:44 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	release_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

int	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	if (stop_check(philo) || death_check(philo))
	{
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		return (1);
	}
	if (philo->data->num_philos == 1)
		return (0);
	sem_wait(philo->data->forks);
	if (stop_check(philo) || death_check(philo))
	{
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		return (1);
	}
	return (0);
}

void	print_fork_taken(t_philo *philo)
{
	printf("%ld %d has taken a fork\n", get_time_in_ms(), philo->id);
	printf("%ld %d has taken a fork\n", get_time_in_ms(), philo->id);
}

int	philo_sleeping(t_philo *philo)
{
	long	start_time;

	start_time = get_time_in_ms();
	printf("%ld %d is sleeping\n", get_time_in_ms(), philo->id);
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
	printf("%ld %d is thinking\n", get_time_in_ms(), philo->id);
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
	printf("%ld %d is eating\n", get_time_in_ms(), philo->id);
	while (get_time_in_ms() - start_time < philo->data->time_to_eat)
	{
		if (stop_check(philo) || death_check(philo))
			return (release_forks(philo), 1);
		usleep(10);
	}
	release_forks(philo);
	philo->meals_eaten++;
	return (0);
}

void	*single_philo_routine(t_philo *philo)
{
	sem_wait(philo->data->forks);
	printf("%ld %d has taken a fork\n", get_time_in_ms(), philo->id);
	while (!death_check(philo))
		usleep(10);
	sem_post(philo->data->forks);
	return (NULL);
}

void	*philo_routine(t_philo *philo)
{
	if (philo->data->num_philos == 1)
		return (single_philo_routine(philo));
	while (!stop_check(philo) && !death_check(philo))
	{
		if (take_forks(philo) == 1)
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
