/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:10:56 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/12/22 18:46:50 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int p_eat(t_philo *philo)
{
	// message("trying to eat\n", philo);
	if (take_fork(philo->right_fork, philo) || take_fork(philo->left_fork, philo))
		return (message("DEATH BY FKN FORK\n", philo), 1);
	philo->eta_death = now() + philo->table->time_to_die;
	pthread_mutex_lock(&philo->table->dead_lock);
	if (check_death(philo))
		return (1);
	pthread_mutex_unlock(&philo->table->dead_lock);
	// pthread_mutex_lock(&philo->table->print_lock);
	// printf("%lu %d is eating\n", now(), philo->id);
	message("is eating\n", philo);
	// pthread_mutex_unlock(&philo->table->print_lock);
	if (sleep_till_death(philo->table->time_to_eat, philo))
		return (1);
	drop_forks(philo);
	return (0);
}

int p_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (check_death(philo))
		return (1);
	pthread_mutex_unlock(&philo->table->dead_lock);
	// pthread_mutex_lock(&philo->table->print_lock);
	// printf("%lu %d is sleeping\n", now(), philo->id);
	message("is sleeping\n", philo);
	// pthread_mutex_unlock(&philo->table->print_lock);
	if (sleep_till_death(philo->table->time_to_sleep, philo))
		return (1);
	return (0);
}

int p_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (check_death(philo))
		return (1);
	pthread_mutex_unlock(&philo->table->dead_lock);
	// pthread_mutex_lock(&philo->table->print_lock);
	// printf("%lu %d is thinking\n", now(), philo->id);
	message("is thinking\n", philo);
	// pthread_mutex_unlock(&philo->table->print_lock);
	return (0);
}

void p_death(t_philo *philo)
{
	// printf("%lu %d died\n", now(), philo->id);
	if (philo->table->death_flag == 0)
	{
		// pthread_mutex_lock(&philo->table->print_lock);
		// printf("%lu %d died\n", now(), philo->id);
		message("died\n", philo);
		// pthread_mutex_unlock(&philo->table->print_lock);
		philo->table->death_flag = 1;
	}
}
