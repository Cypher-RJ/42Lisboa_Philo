/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cypher <rcesar-d@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:26:32 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/24 12:44:23 by cypher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (is_dead(data))
		return ;
	pthread_mutex_lock(&data->print);
	if (!is_dead(data))
		printf("%lld %d is sleeping\n",
			timestamp() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print);
	precise_sleep(data->time_to_sleep, philo);
	if (is_dead(data))
		return ;
}

void	philo_think(t_philo *philo)
{
	t_data		*data;
	long long	think_time;

	data = philo->data;
	if (is_dead(data))
		return ;
	pthread_mutex_lock(&data->print);
	if (!is_dead(data))
		printf("%lld %d is thinking\n",
			timestamp() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print);
	if (data->philo_count % 2 == 1)
	{
		think_time = (data->time_to_eat * 2) - data->time_to_sleep;
		if (think_time > 0 && think_time < data->time_to_die
			&& data->time_to_die > 400)
			precise_sleep(think_time, philo);
	}
}
