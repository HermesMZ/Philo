/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:41:34 by zoum              #+#    #+#             */
/*   Updated: 2025/09/09 17:18:59 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	set_fork_order(t_philo *philo, int *first_fork, int *second_fork)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}

int	take_forks(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	if (stop_check(philo) || death_check(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (1);
	}
	if (second_fork != first_fork)
	{
		pthread_mutex_lock(&philo->data->forks[second_fork]);
		if (stop_check(philo) || death_check(philo))
		{
			pthread_mutex_unlock(&philo->data->forks[first_fork]);
			pthread_mutex_unlock(&philo->data->forks[second_fork]);
			return (1);
		}
	}
	else if (stop_check(philo) || death_check(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (1);
	}
	return (0);
}

void	print_fork_taken(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n", get_time_in_ms(), philo->id);
		printf("%ld %d has taken a fork\n", get_time_in_ms(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
}
