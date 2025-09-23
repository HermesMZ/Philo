/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:13:05 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/17 13:48:13 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_sleeping(t_philo *philo)
{
	long	start_time;

	if (philo->should_stop || death_check(philo))
		return (1);
	start_time = get_time_in_ms();
	safe_print(philo, "is sleeping");
	while (get_time_in_ms() - start_time < philo->data->time_to_sleep)
	{
		if (death_check(philo))
			return (1);
		usleep(10);
	}
	return (0);
}

int	philo_thinking(t_philo *philo)
{
	if (philo->should_stop || death_check(philo))
		return (1);
	safe_print(philo, "is thinking");
	usleep(50);
	return (philo->should_stop || death_check(philo));
}

void	*single_philo_routine(t_philo *philo)
{
	sem_wait(philo->data->forks);
	safe_print(philo, "has taken a fork");
	while (!philo->should_stop && !death_check(philo))
		usleep(100);
	sem_post(philo->data->forks);
	return (NULL);
}

void	*philo_routine(t_philo *philo)
{
	if (philo->data->num_philos == 1)
		return (single_philo_routine(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->should_stop && !death_check(philo))
	{
		if (take_forks(philo) == 1)
			break ;
		if (philo_eating(philo) == 1)
			break ;
		if (philo_sleeping(philo) == 1)
			break ;
		if (philo_thinking(philo) == 1)
			break ;
	}
	return (NULL);
}
