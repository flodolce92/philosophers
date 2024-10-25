/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:10:56 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/10/25 09:52:42 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lu %d is eating\n", now(), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lu %d is sleeping\n", now(), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
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
