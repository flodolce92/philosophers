/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:43:15 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/08/23 18:18:04 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	flip_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->forks[i].fork_lock);
		pthread_mutex_destroy(&table->philos[i].philo_lock);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->dead_lock);
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
}

int	throw_error(char *error, t_table *table, int exit_code)
{
	printf("Error %d: %s\n", exit_code, error);
	if (table)
		flip_table(table);
	return (exit_code);
}

/*	argvs[1-5]:
	number_of_philosophers
	time_to_die
	time_to_eat
	time_to_sleep
	[number_of_times_each_philosopher_must_eat]
*/
int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Wrong number of argouments.\n"), 1);
	if (isalldigit(argv[1]) || ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
		return (printf("Invalid number of philosophers.\n"), 1);
	if (isalldigit(argv[2]) || ft_atoi(argv[2]) <= 0)
		return (printf("Invalid die time\n"), 1);
	if (isalldigit(argv[3]) || ft_atoi(argv[3]) <= 0)
		return (printf("Invalid eat time\n"), 1);
	if (isalldigit(argv[4]) || ft_atoi(argv[4]) <= 0)
		return (printf("Invalid sleep time\n"), 1);
	if (argv[5] && (isalldigit(argv[5]) || ft_atoi(argv[5]) < 0))
		return (printf("Invalid number of meals\n"), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc, argv))
		return (1);
	if (init(&table, argc, argv))
		return (1);
	start_dinner(&table);
	flip_table(&table);
	return (0);
}
