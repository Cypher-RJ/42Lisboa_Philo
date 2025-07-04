/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:26:32 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/04 13:26:33 by rcesar-d         ###   ########.fr       */
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
	printf("%lld %d is sleeping\n",
		timestamp() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print);
	precise_sleep(data->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (is_dead(data))
		return ;
	pthread_mutex_lock(&data->print);
	printf("%lld %d is thinking\n",
		timestamp() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print);
}
