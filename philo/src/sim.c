/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:26:56 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/16 14:39:11 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread,
				NULL, philo_routine, &data->philos[i]) != 0)
		{
			printf("Error: failed to create thread \
				for philosopher %d\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor_thread;

	if (create_threads(data))
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
	{
		printf("Error: failed to create monitor thread\n");
		return (1);
	}
	pthread_join(monitor_thread, NULL);
	join_threads(data);
	return (0);
}
