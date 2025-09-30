/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:41:34 by zoum              #+#    #+#             */
/*   Updated: 2025/09/30 14:53:42 by zoum             ###   ########.fr       */
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
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (1);
	}
	if (second_fork != first_fork)
	{
		pthread_mutex_lock(&philo->data->forks[second_fork]);
		if (should_stop(philo))
		{
			pthread_mutex_unlock(&philo->data->forks[first_fork]);
			pthread_mutex_unlock(&philo->data->forks[second_fork]);
			return (1);
		}
	}
	else if (should_stop(philo))
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
		safe_print(philo, "has taken a fork");
		safe_print(philo, "has taken a fork");
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
}
