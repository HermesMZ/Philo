/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:27:05 by zoum              #+#    #+#             */
/*   Updated: 2025/09/09 17:19:37 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char *argv[])
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0' || j > 10)
				return (printf("Error: Invalid input\n"), 0);
			j++;
		}
		if (ft_atoi(argv[i]) != ft_atol(argv[i])
			|| ft_atoi(argv[i]) > 2147483647)
			return (printf("Error: Invalid input\n"), 0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (printf("Error: Invalid number of arguments.\n"), 1);
	if (!check_input(argc, argv))
		return (1);
	data = init_data(argc, argv);
	if (!data)
		return (printf("Error: Failed to initialize data.\n"), 1);
	init_philos_and_mutex(data);
	start_simulation(data);
	clean_all(data);
	return (0);
}
