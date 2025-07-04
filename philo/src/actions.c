/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:26:38 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/04 13:26:39 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	print_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	printf("%lld %d has taken a fork\n",
		timestamp() - data->start_time, philo->id);
	printf("%lld %d has taken a fork\n",
		timestamp() - data->start_time, philo->id);
	printf("%lld %d is eating\n",
		timestamp() - data->start_time, philo->id);
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (is_dead(data))
		return ;
	lock_forks(philo);
	if (is_dead(data))
	{
		unlock_forks(philo);
		return ;
	}
	pthread_mutex_lock(&data->print);
	if (!is_dead(data))
		print_eat(philo);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = timestamp();
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
	precise_sleep(data->time_to_eat, philo);
	unlock_forks(philo);
}
