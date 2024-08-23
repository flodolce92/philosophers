/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:50:26 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/08/23 18:19:18 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eaten_meals = 0;
		table->philos[i].eating = 0;
		table->philos[i].last_meal = 0;
		pthread_mutex_init(&table->forks[i].fork_lock, NULL);
		table->forks[i].in_use = 0;
		table->philos[i].left_fork = &(table->forks[i]);
		table->philos[i].right_fork = &(table->forks[(i + 1) % table->n_philo]);
		pthread_mutex_init(&table->philos[i].philo_lock, NULL);
		table->philos[i].table = table;
		i++;
	}
	return (0);
}

int	init_table(t_table *table, int argc, char **argv)
{
	table->n_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->max_meals = ft_atoi(argv[5]);
	else
		table->max_meals = -1;
	table->philos = (t_philo *) malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		return (1);
	table->forks = (t_fork *) malloc(sizeof(t_fork) * table->n_philo);
	if (!table->forks)
		return (1);
	table->start_time = 0;
	table->death_flag = 0;
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	return (0);
}

int	init(t_table *table, int argc, char **argv)
{
	if (init_table(table, argc, argv))
		return (1);
	if (init_philos(table))
		return (1);
	return (0);
}
