/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:40:38 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/10/25 09:50:17 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	while (1)
	{
		pthread_mutex_lock(&philo->table->dead_lock);
		if (philo->table->death_flag == 1)
		{
			p_death(philo);
			break;
		}
		pthread_mutex_unlock(&philo->table->dead_lock);
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (philo);
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
}
