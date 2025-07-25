/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:26:48 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/16 14:43:30 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (check_syntax(ac, av, &data))
		return (1);
	if (init_data(&data))
		return (1);
	if (init_philos(&data))
		return (1);
	if (start_simulation(&data))
		return (1);
	destroy_all(&data);
	return (0);
}
