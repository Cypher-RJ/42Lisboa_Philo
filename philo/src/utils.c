/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:27:06 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/04 15:17:00 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_strcmp(const char *instr, const char *comparing)
{
	int	i;

	i = 0;
	while (instr[i] == comparing[i] && instr[i])
		i++;
	return (instr[i] - comparing[i]);
}

int	is_valid_digit_str(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (i > 0);
}

int	atoi_positive_lda(const char *str, const char *arg_name, int max)
{
	long long	result;
	int			i;

	if (!is_valid_digit_str(str))
		return (arg_error(arg_name, "must be a positive integer"));
	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > max || result > INT_MAX)
			return (arg_error(arg_name, "is too large"));
		i++;
	}
	if (ft_strcmp(arg_name, "number_of_philosophers") == 0 && result == 0)
		return (arg_error(arg_name, "must not be 0"));
	return ((int)result);
}
