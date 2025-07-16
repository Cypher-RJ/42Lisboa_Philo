/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:26:50 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/16 13:39:01 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_philo(t_data *data, int i, int *all_ate)
{
	long long	now;
	long long	last_meal;
	int			meals;

	now = timestamp();
	pthread_mutex_lock(&data->philos[i].meal_mutex);
	last_meal = data->philos[i].last_meal;
	meals = data->philos[i].meals;
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	if ((now - last_meal) > data->time_to_die)
	{
		pthread_mutex_lock(&data->print);
		if (!is_dead(data))
		{
			set_dead(data);
			printf("%lld %d died\n",
				now - data->start_time, data->philos[i].id);
		}
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	if (data->meals_required > 0 && meals < data->meals_required)
		*all_ate = 0;
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		all_ate;

	data = (t_data *)arg;
	while (!is_dead(data))
	{
		i = 0;
		all_ate = 1;
		while (i < data->philo_count)
		{
			if (check_philo(data, i, &all_ate))
				return (NULL);
			i++;
		}
		if (data->meals_required > 0 && all_ate)
		{
			set_dead(data);
			return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}
