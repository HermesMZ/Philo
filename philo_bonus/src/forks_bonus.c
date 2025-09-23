/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:13:10 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/17 14:05:30 by mzimeris         ###   ########.fr       */
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
	if (philo->should_stop || death_check(philo))
		return (1);
	sem_wait(philo->data->forks);
	safe_print(philo, "has taken a fork");
	if (philo->should_stop || death_check(philo))
	{
		sem_post(philo->data->forks);
		return (1);
	}
	if (philo->data->num_philos == 1)
		return (0);
	sem_wait(philo->data->forks);
	safe_print(philo, "has taken a fork");
	if (philo->should_stop || death_check(philo))
	{
		release_forks(philo);
		return (1);
	}
	return (0);
}

int	philo_eating(t_philo *philo)
{
	long	start_time;

	start_time = get_time_in_ms();
	if (philo->should_stop || death_check(philo))
		return (1);
	safe_print(philo, "is eating");
	while (get_time_in_ms() - start_time < philo->data->time_to_eat)
	{
		if (philo->should_stop || death_check(philo))
			return (release_forks(philo), 1);
		usleep(10);
	}
	philo->last_meal_time = get_time_in_ms();
	release_forks(philo);
	philo->meals_eaten++;
	if (philo->data->num_meals != -1
		&& philo->meals_eaten == philo->data->num_meals)
	{
		sem_post(philo->data->meals_done);
	}
	return (0);
}
