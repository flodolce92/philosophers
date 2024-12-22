/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:10:56 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/12/22 22:47:32 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_eat(t_philo *philo)
{
	if (take_fork(philo->right_fork, philo) \
	|| take_fork(philo->left_fork, philo))
		return (1);
	philo->eta_death = now() + philo->table->time_to_die;
	pthread_mutex_lock(&philo->table->dead_lock);
	if (check_death(philo))
		return (1);
	pthread_mutex_unlock(&philo->table->dead_lock);
	message("is eating\n", philo);
	if (sleep_till_death(philo->table->time_to_eat, philo))
		return (1);
	drop_forks(philo);
	return (0);
}

int	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (check_death(philo))
		return (1);
	pthread_mutex_unlock(&philo->table->dead_lock);
	message("is sleeping\n", philo);
	if (sleep_till_death(philo->table->time_to_sleep, philo))
		return (1);
	return (0);
}

int	p_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (check_death(philo))
		return (1);
	pthread_mutex_unlock(&philo->table->dead_lock);
	message("is thinking\n", philo);
	return (0);
}

void	p_death(t_philo *philo)
{
	if (philo->table->death_flag == 0)
	{
		message("died\n", philo);
		philo->table->death_flag = 1;
	}
}
