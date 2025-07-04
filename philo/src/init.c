/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:26:43 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/04 13:26:44 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_data(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
	{
		free(data->forks);
		return (1);
	}
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
		return (1);
	data->dead = 0;
	data->start_time = timestamp();
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		i++;
	}
	return (0);
}
