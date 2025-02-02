/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:40:38 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/12/22 23:17:01 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	philo->eta_death = now() + philo->table->time_to_die;
	if (philo->id % 2 == 0)
	{
		if (sleep_till_death(philo->table->time_to_eat / 3, philo))
			return (NULL);
	}
	while (philo->eaten_meals != philo->table->max_meals)
	{
		if (check_death(philo))
			return (NULL);
		if (p_eat(philo) || p_sleep(philo) || p_think(philo))
			return (NULL);
		if (philo->table->max_meals != -1)
			philo->eaten_meals++;
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, \
		routine_philo, &table->philos[i]))
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
