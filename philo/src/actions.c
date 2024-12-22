/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:10:56 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/12/22 03:02:18 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_eat(t_philo *philo)
{
	if (take_fork(philo->right_fork, philo) || take_fork(philo->left_fork, philo))
		return (1);
	// if(take_forks(philo) == 1)
	// 	return (1);
	// pthread_mutex_lock(&philo->table->print_lock);
	// printf("%lu %d is eating\n", now(), philo->id);
	// pthread_mutex_unlock(&philo->table->print_lock);
	// pthread_mutex_lock(&philo->philo_lock);
	// philo->last_meal = now();
	// philo->eaten_meals++;
	// pthread_mutex_unlock(&philo->philo_lock);
	// usleep(philo->table->time_to_eat * 1000);
	// drop_forks(philo);
	return (0);
}

int	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lu %d is sleeping\n", now(), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
	usleep(philo->table->time_to_sleep * 1000);
	return (0);
}

int	p_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lu %d is thinking\n", now(), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (0);
}

void	p_death(t_philo *philo)
{
	ptrhread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->death_flag == 0)
	{
		pthread_mutex_lock(&philo->table->print_lock);
		printf("%lu %d died\n", now(), philo->id);
		pthread_mutex_unlock(&philo->table->print_lock);
		philo->table->death_flag = 1;
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
}
