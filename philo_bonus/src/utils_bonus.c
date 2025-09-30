/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:12:55 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/30 14:56:10 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time_in_ms(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

void	safe_print(t_philo *philo, const char *message)
{
	if (!philo->should_stop)
	{
		sem_wait(philo->data->writing);
		if (!philo->should_stop)
			printf("%10ld %3d %s\n", get_time_in_ms()
				- philo->data->start_time, philo->id, message);
		sem_post(philo->data->writing);
	}
}

void	clean_semaphores(t_data *data)
{
	if (data->writing && data->writing != SEM_FAILED)
		sem_close(data->writing);
	if (data->stop && data->stop != SEM_FAILED)
		sem_close(data->stop);
	if (data->forks && data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->meals_done && data->meals_done != SEM_FAILED)
		sem_close(data->meals_done);
}

void	cleanup(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->pid)
		free(data->pid);
	clean_semaphores(data);
	free(data);
}

void	final_cleanup(t_data *data)
{
	cleanup(data);
	sem_unlink("/writing_sem");
	sem_unlink("/stop_sem");
	sem_unlink("/forks_sem");
	sem_unlink("/meals_done_sem");
}
