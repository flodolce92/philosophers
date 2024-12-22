/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:40:38 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/12/22 02:37:52 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *p)
{
	t_philo	*philo;
	int 	eaten_meals;

	philo = (t_philo *) p;
	eaten_meals = 0;
	while (eaten_meals != philo->table->max_meals)
	{
		if (p_eat(philo) || p_sleep(philo) || p_think(philo))
			return (NULL);
		if (philo->table->max_meals != -1)
			eaten_meals++;
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = now();
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, routine_philo, &table->philos[i]))
			throw_error("pthread_create failed", table, 1);
		i++;
	}
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			throw_error("pthread_join failed", table, 1);
		i++;
	}
}
