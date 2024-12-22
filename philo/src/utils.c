/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:47:02 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/12/22 22:21:11 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

int	isalldigit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

size_t	now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		throw_error("gettimeofday() error\n", NULL, 1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_usage(void)
{
	printf("usage: philo \t[number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep]\n\
\t\t[number_of_times_each_philosopher_must_eat]\n");
}

int	throw_error(char *error, t_table *table, int exit_code)
{
	printf("Error %d: %s\n", exit_code, error);
	if (table)
		flip_table(table);
	return (exit_code);
}
