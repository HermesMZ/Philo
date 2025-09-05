/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:27:05 by zoum              #+#    #+#             */
/*   Updated: 2025/09/05 01:36:15 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (printf("Error: Invalid number of arguments.\n"), 1);
	data = init_data(argc, argv);
	if (!data)
		return (printf("Error: Failed to initialize data.\n"), 1);
	init_philos_and_mutex(data);
	start_simulation(data);
	clean_all(data);
	return (0);
}
