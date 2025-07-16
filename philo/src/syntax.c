/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:27:03 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/16 14:43:48 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_syntax(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep \
				[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	data->philo_count = atoi_positive_lda(argv[1],
			"number_of_philosophers", 200);
	data->time_to_die = atoi_positive_lda(argv[2],
			"time_to_die", INT_MAX);
	data->time_to_eat = atoi_positive_lda(argv[3],
			"time_to_eat", INT_MAX);
	data->time_to_sleep = atoi_positive_lda(argv[4], "time_to_sleep", INT_MAX);
	if (argc == 6)
		data->meals_required = atoi_positive_lda(argv[5],
				"number_of_times_each_philosopher_must_eat", INT_MAX);
	else
		data->meals_required = -1;
	if (data->philo_count == -1 || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1
		|| (argc == 6 && data->meals_required == -1))
		return (1);
	return (0);
}
