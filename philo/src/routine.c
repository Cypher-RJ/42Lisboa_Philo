/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:26:53 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/04 13:26:54 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	routine_solo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&data->print);
	printf("%lld %d has taken a fork\n",
		timestamp() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print);
	precise_sleep(data->time_to_die, philo);
	pthread_mutex_unlock(philo->left_fork);
}

static void	routine_loop(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(200);
	while (!is_dead(data)
		&& (data->meals_required == -1
			|| philo->meals < data->meals_required))
	{
		if (is_dead(data))
			break ;
		philo_eat(philo);
		if (is_dead(data))
			break ;
		philo_sleep(philo);
		if (is_dead(data))
			break ;
		philo_think(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		routine_solo(philo);
		return (NULL);
	}
	routine_loop(philo);
	return (NULL);
}
