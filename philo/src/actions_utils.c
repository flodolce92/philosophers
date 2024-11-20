/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:55:58 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/11/20 16:45:53 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_lock);
	if (philo->right_fork->in_use == 1)
	{
		pthread_mutex_unlock(&philo->right_fork->fork_lock);
		return (1);
	}
	philo->right_fork->in_use = 1;
	pthread_mutex_unlock(&philo->right_fork->fork_lock);
	pthread_mutex_lock(&philo->left_fork->fork_lock);
	if (philo->left_fork->in_use == 1)
	{
		pthread_mutex_unlock(&philo->left_fork->fork_lock);
		pthread_mutex_lock(&philo->right_fork->fork_lock);
		philo->right_fork->in_use = 0;
		pthread_mutex_unlock(&philo->right_fork->fork_lock);
		return (1);
	}
	philo->left_fork->in_use = 1;
	pthread_mutex_unlock(&philo->left_fork->fork_lock);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_lock);
	philo->right_fork->in_use = 0;
	pthread_mutex_unlock(&philo->right_fork->fork_lock);
	pthread_mutex_lock(&philo->left_fork->fork_lock);
	philo->left_fork->in_use = 0;
	pthread_mutex_unlock(&philo->left_fork->fork_lock);
}
