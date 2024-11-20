/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:10:56 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/11/20 16:49:24 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_eat(t_philo *philo)
{
	if(take_forks(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lu %d is eating\n", now(), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = now();
	philo->eaten_meals++;
	pthread_mutex_unlock(&philo->philo_lock);
	usleep(philo->table->time_to_eat * 1000);
	drop_forks(philo);
	return (0);
}

void	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lu %d is sleeping\n", now(), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
	usleep(philo->table->time_to_sleep * 1000);
}

void	p_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lu %d is thinking\n", now(), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	p_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lu %d died\n", now(), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}
