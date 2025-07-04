/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:26:58 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/04 16:02:13 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	precise_sleep(long long ms, t_philo *philo)
{
	long long	start;

	start = timestamp();
	while (!is_dead(philo->data))
	{
		if (timestamp() - start >= ms)
			break ;
		usleep(10);
	}
}

int	is_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_mutex);
	dead = data->dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (dead);
}

void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}
